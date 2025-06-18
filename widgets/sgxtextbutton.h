#ifndef SGXTEXTBUTTON_H
#define SGXTEXTBUTTON_H

#include <QWidget>
#include <QPushButton>
#include "../userDefinedClasses/sgusignalemitter.h"
#include "../primitives/sgxcolourrgba.h"
#include <QString>
#include <QFont>
#include <QColor>
#include <QEvent>

class SGXTextButton : public QPushButton // interactive button with text display
{
    Q_OBJECT // NOLINT
public:
    SGXTextButton(QWidget* parent, void (SGUSignalEmitter::*resizeSignal)(), const QString& s, void (*attachedFunction)(), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0); // create text button
    // the value of each size and location variable is linear factor * width or height of rendering space + constant factor * size unit
    // ensure that x0 + w0 < 13.5 * (1 - x1 - w1) and y0 + h0 < 13.5 * (1 - y1 - h1) to avoid widgets going off screen
    // you are recommended to keep 0.5 * size unit of margin on the 4 sides of the screen
    float x1; // linear factor of x position
    float x0; // constant factor of x position
    float y1; // linear factor of y position
    float y0; // constant factor of y position
    float w1; // linear factor of width
    float w0; // constant factor of width
    float h1; // linear factor of height
    float h0; // constant factor of height
    bool unselected; // indicates if button is unselected
    bool hovering; // indicates if button is hovered over
    bool pressed; // indicates if button is being pressed
    QColor backgroundColour; // colour used to shade background
    QColor foregroundColour; // colour used to shade text
    QColor hoverBackgroundColour; // colour used to shade background when hovered over
    QColor hoverForegroundColour; // colour used to shade text when hovered over
    QColor pressedBackgroundColour; // colour used to shade background when pressed
    QColor pressedForegroundColour; // colour used to shade text when pressed
    QColor unselectedBackgroundColour; // colour used to shade background when unselected
    QColor unselectedForegroundColour; // colour used to shade text when unselected
    QColor unselectedHoverBackgroundColour; // colour used to shade background when unselected and hovered over
    QColor unselectedHoverForegroundColour; // colour used to shade text when unselected and hovered over
    QString s; // text displayed in button
    QFont font; // font used for button with size set
    void setText(const QString& s); // function to change text and update widget
    void setBackgroundColour(); // set background colour to default colour
    void setBackgroundColour(int themeColourIndex); // set background colour to theme colour
    void setBackgroundColour(SGXColourRGBA customColour); // set background colour to custom colour
    void setForegroundColour(); // set text colour to default colour
    void setForegroundColour(int themeColourIndex); // set text colour to theme colour
    void setForegroundColour(SGXColourRGBA customColour); // set text colour to custom colour
    void setHoverBackgroundColour(); // set background colour when hovering to default colour
    void setHoverBackgroundColour(int themeColourIndex); // set background colour when hovering to theme colour
    void setHoverBackgroundColour(SGXColourRGBA customColour); // set background colour when hovering to custom colour
    void setHoverForegroundColour(); // set text colour when hovering to default colour
    void setHoverForegroundColour(int themeColourIndex); // set text colour when hovering to theme colour
    void setHoverForegroundColour(SGXColourRGBA customColour); // set text colour when hovering to custom colour
    void setPressedBackgroundColour(); // set background colour when pressed to default colour
    void setPressedBackgroundColour(int themeColourIndex); // set background colour when pressed to theme colour
    void setPressedBackgroundColour(SGXColourRGBA customColour); // set background colour when pressed to custom colour
    void setPressedForegroundColour(); // set text colour when pressed to default colour
    void setPressedForegroundColour(int themeColourIndex); // set text colour when pressed to theme colour
    void setPressedForegroundColour(SGXColourRGBA customColour); // set text colour when pressed to custom colour
    void setUnselectedBackgroundColour(); // set background colour when unselected to default colour
    void setUnselectedBackgroundColour(int themeColourIndex); // set background colour when unselected to theme colour
    void setUnselectedBackgroundColour(SGXColourRGBA customColour); // set background colour when unselected to custom colour
    void setUnselectedForegroundColour(); // set text colour when unselected to default colour;
    void setUnselectedForegroundColour(int themeColourIndex); // set text colour when unselected to theme colour
    void setUnselectedForegroundColour(SGXColourRGBA customColour); // set text colour when unselected to custom colour
    void setUnselectedHoverBackgroundColour(); // set background colour when unselected and hovered over to default colour
    void setUnselectedHoverBackgroundColour(int themeColourIndex); // set background colour when unselected and hovered over to theme colour
    void setUnselectedHoverBackgroundColour(SGXColourRGBA customColour); // set background colour when unselected and hovered over to custom colour
    void setUnselectedHoverForegroundColour(); // set text colour when unselected and hovered over to default colour
    void setUnselectedHoverForegroundColour(int themeColourIndex); // set text colour when unselected and hovered over to theme colour
    void setUnselectedHoverForegroundColour(SGXColourRGBA customColour); // set text colour when unselected and hovered over to custom colour
    void enterEvent(QEnterEvent*) override; // NOLINT(readability-named-parameter)
    void leaveEvent(QEvent*) override; // NOLINT(readability-named-parameter)
    void mousePressEvent(QMouseEvent* event) override; // update button appearance when pressed
    void mouseReleaseEvent(QMouseEvent* event) override; // update button appearance when released
    void paintEvent(QPaintEvent*) override; // NOLINT(readability-named-parameter)
public slots: // NOLINT
    void resizeObject(); // automatic resizing of text button
};

#endif // SGXTEXTBUTTON_H
