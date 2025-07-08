#ifndef SGXQUICKUIINTERFACE_H
#define SGXQUICKUIINTERFACE_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQuickItem>
#include "../quickui/sgxquickresizer.h"
#include "../quickui/sgxthemecoloursetting.h"
#include "../primitives/sgxtouchevent.h"
#include <qcontainerfwd.h>
#include <qtmetamacros.h>
#include <array>
#include "../primitives/sgxcolourrgba.h"

class SGXQuickUIInterface : public QObject // non instantiable class used to manage SGEXTN widget components
{
    Q_OBJECT
public:
    SGXQuickUIInterface() = delete;
    enum WidgetType{ // list of possible widget types
        Undefined = 0, // is not SGEXTN widget
        RootWidget = 10, // root widget
        ParentWidget = 20, // parent widget, all your widgets should be its direct or indirect children
        Widget = 30, // non interactive widget with a solid colour that blocks input, can be used as background
        Text = 40, // non interactive text widget
        Title = 41, // title widget, essentially center aligned text
        LongText = 42, // non interactive text widget with a scroll bar
        Icon = 43, // non interactive icon widget
        TextButton = 50, // button with text on it
        IconButton = 51, // button with icon on it
        InputField = 60, // single line input field
        LongInputField = 61, // multiline input field
        ScrollView = 70, // scroll view
        TouchReceiver = 80, // widget to receive precise touch
        CuteVesicles = 90, // animation of vesicles
        StatusBar = 100, // status bar
        ColourPicker = 110 // colour picker
    };
    static QQmlApplicationEngine* e; // reference to Qt Quick engine
    static SGXQuickResizer* resizerInstance; // instance of QML Resizer singleton
    static SGXThemeColourSetting* themeColoursInstance; // instance of QML ThemeColours singleton
    static void initialise(); // prepare QML components for usage
    static void terminate(); // delete templates
    static void buildTemplate(); // build basic application parts including the status bar, the root widget, and the parent widget
    static QQuickWindow* applicationWindow; // reference to application window
    static QQuickItem* rootWindow; // reference to application window
    static QQmlComponent* rootWidgetTemplate; // QML template for root widget
    static QQuickItem* createRootWidget(QQuickItem* parent); // function to create a root widget
    static QQuickItem* rootWidget; // reference to root widget
    static QQmlComponent* parentWidgetTemplate; // QML template for parent widget
    static QQuickItem* createParentWidget(QQuickItem* parent); // function to create a parent widget
    static QQuickItem* parentWidget; // reference to parent widget
    // below are SGEXTN widgets that you can use to build your application
    // the size variables are x for x position, y for y position, w for width, h for height, f for font size, s for scroll bar width, and ih for height of scrollable content
    // widget with icons must be squares, so they do not have a h variable
    // if a widget with text does not have a f variable, it is single line and the font size follows its height
    // if a widget with a scrollable area does not have a ih variable, its scrollable area can freely change its height
    // for each variable k, you can set k1 and k0, this would fix k at k1 * a + k0 * b, where a is the width or height of the parent widget depending on context and b is a size unit, which corresponds to 1/24 of the width or height of the parent widget, whichever is greater
    // you can use QObject::setProperty("fontClass") to change the font on widget with text
    // for best compatibility, your icons font file must have the font family "SingScript.sg" and use the Unicode Fxxx private use range
    // you can use SGXQuickUIInterface::getInputFieldDataAs[data type] functions to get data from a input field
    // you can use SGXQuickUIInterface::getClickedButton to determine which button is pressed, if any, since functions attached to buttons do not allow sending back data about which button is it
    // only the parent widgets, widgets, and scroll views can be parents, other widgets such as text widgets, buttons, or input fields cannot, attempting to assign children to a widget that does not accept children would trigger immediate crash of the application to avoid memory leaks and damaging the UI structure
    // to change the parent of a SGEXTN widget, you must use SGXQuickUIInterface::setActualParent and not QObject::setParent or QQuickItem::setParentItem, attempting to use non SGEXTN functions to set parent would damage the UI structure
    // use SGXQuickUIInterface::getActiveObject to determine which button is pressed in multiple button with same attached function setups such as file system lists
    static QQmlComponent* widgetTemplate; // QML template for widget
    static QQuickItem* createWidget(QQuickItem* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, int bg); // function to create a widget, bg is the theme colour index for its background colour
    static QQmlComponent* textTemplate; // QML template for text widget
    static QQuickItem* createText(QQuickItem* parent, const QString& s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0); // function to create a text widget, where s is the text to display
    static QQmlComponent* titleTemplate; // QML template for title widget
    static QQuickItem* createTitle(QQuickItem* parent, const QString& s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0); // function to create a title widget, where s is the text to display
    static QQmlComponent* longTextTemplate; // QML template for long text widget
    static QQuickItem* createLongText(QQuickItem* parent, const QString& s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float f1, float f0, float s1, float s0); // function to create a long text widget, where s is the text to display
    static QQmlComponent* iconTemplate; // QML template for icon
    static QQuickItem* createIcon(QQuickItem* parent, const QChar& s, float x1, float x0, float y1, float y0, float w1, float w0); // function to create a icon, where s is the character for the icon
    static QQmlComponent* textButtonTemplate; // QML template for text button
    static QQuickItem* createTextButton(QQuickItem* parent, const QString& s, void (*attachedFunction)(), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0); // function to create a text button, where s is the text to be displayed and attachedFunction is the function to be run when the button is pressed, the function must be static, return void, and not take any arguments
    static QQmlComponent* iconButtonTemplate; // QML template for icon button
    static QQuickItem* createIconButton(QQuickItem* parent, const QChar& s, void (*attachedFunction)(), float x1, float x0, float y1, float y0, float w1, float w0); // function to create a icon button, where s is the icon to be displayed and attachedFunction is the function to be run when the button is pressed, the function must be static, return void, and not take any arguments
    static QQmlComponent* inputFieldTemplate; // QML template for single line input field
    static QQuickItem* createInputField(QQuickItem* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0); // function to create a single line input field
    static QQmlComponent* longInputFieldTemplate; // QML template for multi line input field
    static QQuickItem* createLongInputField(QQuickItem* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float f1, float f0, float s1, float s0); // function to create a multi line input field
    static QQmlComponent* scrollViewTemplate; // QML template for scroll view
    static QQuickItem* createScrollView(QQuickItem* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float ih1, float ih0, float s1, float s0, int bg); // function to create a scoll view where bg is the theme colour index of the background colour
    static QQmlComponent* touchReceiverTemplate; // QML template for touch receiver
    static QQuickItem* createTouchReceiver(QQuickItem* parent, void (*attachedFunction)(const std::array<SGXTouchEvent, 5>&), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0); // function to create a touch receiver, where attachedFunction is the function run when touch events are detected, the function must be static, return void, and take as input by reference a std::array of 5 SGXTouchEvents
    // note that if a certain touch event slot is not filled, the SGXTouchEvent will have its phase be SGXTouchEvent::TouchEnd
    // if more than 5 touch points are present, only the first 5 will be processed and the rest will be ignored
    // you can choose to process less than 5 touch points in your function
    static void receiveTouch(); // function allowing touch receiver to send out signals
    static QVector<void (*)(const std::array<SGXTouchEvent, 5>&)>* touchEventFunctionsList; // list of functions attached to touch receivers
    static QQmlComponent* cuteVesiclesTemplate; // QML template for vesicles animation
    static QQuickItem* createCuteVesicles(QQuickItem* parent); // function to create a vesicles animation
    static SGXQuickUIInterface::WidgetType getType(QQuickItem* x); // function to get the type of a SGEXTN widget
    static QQuickItem* getActualParentableObject(QQuickItem* x); // function to get the QQuickItem in a SGEXTN widget that can have children in a way compatible with SGEXTN, returns nullptr if not found
    static void setActualParent(QQuickItem* obj, QQuickItem* x); // function to change the parent of a SGEXTN widget, crashes application if desired parent is not a SGEXTN widget or cannot have children, x is the parent and obj is the child
    static int getInputFieldDataAsInt(QQuickItem* x, bool& isValid); // retrieve input as int from SGEXTN input fields, isValid checks if the input is valid
    static float getInputFieldDataAsFloat(QQuickItem* x, bool& isValid); // retrieve input as float from SGEXTN input fields, isValid checks if the input is valid
    static QString getInputFieldDataAsString(QQuickItem* x, bool& isValid); // retrieve input as string from SGEXTN input fields, isValid checks if the input is valid, the input is invalid if x is not a SGEXTN input field
    static QQuickItem* getActiveObject(); // get the currently active SGEXTN object, can be used to distinguish which button got pressed when there are multiple buttons
    static QQmlComponent* statusBarTemplate; // QML template for status bar
    static QQuickItem* createStatusBar(QQuickItem* parent); // function to create status bar
    static QQmlComponent* colourPickerTemplate; // QML template for colour picker
    static QQuickItem* createColourPicker(QQuickItem* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, SGXColourRGBA defaultColour); // function to create colour picker with colour initialised to defaultColour
    static SGXColourRGBA getColourPickerColour(QQuickItem* x, bool& isValid); // retrieve input as colour from SGEXTN colour picker, isValid checks if the widget is actually a colour picker
    static bool setInputFieldDataUsingString(QQuickItem* x, const QString& s); // set text in input field, return true if set successfully and false otherwise
    static bool setInputFieldDataUsingInt(QQuickItem* x, int s); // set text in input field to string representaion of a int, return true if set successfully and false otherwise
    static bool setInputFieldDataUsingFloat(QQuickItem* x, float s); // set text in input field to string representation of a float, return true if set successfully and false otherwise
    static bool setColourPickerColour(QQuickItem* x, SGXColourRGBA c); // set colour in a colour picker, return true if set successfully and false otherwise
};

#endif // SGXQUICKUIINTERFACE_H
