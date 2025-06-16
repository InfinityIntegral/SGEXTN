#ifndef SGUCENTRALMANAGEMENT_H
#define SGUCENTRALMANAGEMENT_H

#include <QObject>
#include "../primitives/sgxcolourrgba.h"

class SGUCentralManagement : public QObject // non instantiable class for essential application data that should be define by the user, including application name, theme colours, custom initialisation and custom termination
{
    Q_OBJECT // NOLINT
public:
    SGUCentralManagement() = delete;
    SGUCentralManagement(const SGUCentralManagement&) = delete;
    SGUCentralManagement(SGUCentralManagement&&) = delete;
    SGUCentralManagement& operator=(const SGUCentralManagement&) = delete;
    SGUCentralManagement& operator=(SGUCentralManagement&&) = delete;
    ~SGUCentralManagement() override = default;
    static void initialise(); // initialisation function run when app opens
    static void terminate(); // temination function run when app closes
    static QString applicationName; // name of application displayed
    static QString applicationVersion; // version number of application
    static SGXColourRGBA rootWindowColour; // colour of root window, can be translucent
    // static SGXColourRGBA themeColour0; // theme colour 0
    // static SGXColourRGBA themeColour1; // theme colour 1
    static SGXColourRGBA themeColour2; // theme colour 2
    static SGXColourRGBA themeColour3; // theme colour 3
    static SGXColourRGBA themeColour4; // theme colour 4
    static SGXColourRGBA themeColour5; // theme colour 5
    static SGXColourRGBA themeColour6; // theme colour 6
    static SGXColourRGBA themeColour7; // theme colour 7
    static SGXColourRGBA themeColour8; // theme colour 8
    static SGXColourRGBA textBackgroundColour; // background colour of text labels
    static SGXColourRGBA textForegroundColour; // foreground colour of text labels
    static SGXColourRGBA buttonBackgroundColour; // background colour of button
    static SGXColourRGBA buttonForegroundColour; // foreground colour of button
    static SGXColourRGBA buttonHoverBackgroundColour; // background colour when cursor is hovering over button
    static SGXColourRGBA buttonHoverForegroundColour; // foreground colour when cursor is hovering over button
    static SGXColourRGBA buttonPressedBackgroundColour; // background colour when button is being pressed
    static SGXColourRGBA buttonPressedForegroundColour; // foreground colour when button is being pressed
    static SGXColourRGBA unselectedButtonBackgroundColour; // background colour of button representing unselected options
    static SGXColourRGBA unselectedButtonForegroundColour; // foreground colour of button representing unselected options
    static SGXColourRGBA unselectedButtonHoverBackgroundColour; // background colour of button representing unselected options when being hovered over
    static SGXColourRGBA unselectedButtonHoverForegroundColour; // foreground colour of button representing unselected options when being hovered over
    static SGXColourRGBA inputFieldBackgroundColour; // background colour of input field
    static SGXColourRGBA inputFieldForegroundColour; // foreground colour of input field
    static SGXColourRGBA inputFieldSelectedHighlightBackgroundColour; // background colour of input field selected text
    static SGXColourRGBA inputFieldSelectedHighlightForegroundColour; // foreground colour of input field selected text
    static SGXColourRGBA inputFieldHoverBackgroundColour; // background colour of input field when hovered over
    static SGXColourRGBA inputFieldHoverForegroundColour; // foreground colour of input field when hovered over
    static SGXColourRGBA inputFieldFocusedBackgroundColour; // background colour of input field when focused
    static SGXColourRGBA inputFieldFocusedForegroundColour; // foreground colour of input field when focused
    static SGXColourRGBA scrollBarBackgroundColour; // background colour of scroll bar
    static SGXColourRGBA scrollBarForegroundColour; // foreground colour of scroll bar, applied to scroll bar handle
    static SGXColourRGBA scrollBarForegroundHoverColour; // foreground colour of scroll bar, applied to scroll bar handle when scroll bar is hovered over
    static SGXColourRGBA scrollBarForegroundPressedColour; // foreground colour of scroll bar, applied to scroll bar handle when scroll bar is pressed
};

#endif // SGUCENTRALMANAGEMENT_H
