#ifndef SGXSCROLLBAR_H
#define SGXSCROLLBAR_H

#include <QWidget>
#include <QScrollBar>
#include "../primitives/sgxcolourrgba.h"
#include <QColor>
#include <QEvent>

class SGXScrollBar : public QScrollBar // scroll bar for SGXEXTN, should not be instantiated, only controlled through parent SGXScrollView
{
    Q_OBJECT // NOLINT
public:
    SGXScrollBar(QWidget* parent); // create scroll bar
    // width of scroll bar is w1 * width of rendering space + w0 * size unit;
    bool hovering; // indicates if scroll bar is hovered over
    bool pressed; // indicates if scroll bar is being pressed
    QColor backgroundColour; // colour used to shade background
    QColor foregroundColour; // colour used to shade handle
    QColor hoverBackgroundColour; // colour used to shade background when hovered over
    QColor hoverForegroundColour; // colour used to shade handle when hovered over
    QColor pressedBackgroundColour; // colour used to shade background when pressed
    QColor pressedForegroundColour; // colour used to shade handle when pressed
    void setBackgroundColour(); // set background colour to default colour
    void setBackgroundColour(int themeColourIndex); // set background colour to theme colour
    void setBackgroundColour(SGXColourRGBA customColour); // set background colour to custom colour
    void setForegroundColour(); // set handle colour to default colour
    void setForegroundColour(int themeColourIndex); // set handle colour to theme colour
    void setForegroundColour(SGXColourRGBA customColour); // set handle colour to custom colour
    void setHoverBackgroundColour(); // set background colour when hovering to default colour
    void setHoverBackgroundColour(int themeColourIndex); // set background colour when hovering to theme colour
    void setHoverBackgroundColour(SGXColourRGBA customColour); // set background colour when hovering to custom colour
    void setHoverForegroundColour(); // set handle colour when hovering to default colour
    void setHoverForegroundColour(int themeColourIndex); // set handle colour when hovering to theme colour
    void setHoverForegroundColour(SGXColourRGBA customColour); // set handle colour when hovering to custom colour
    void setPressedBackgroundColour(); // set background colour when pressed to default colour
    void setPressedBackgroundColour(int themeColourIndex); // set background colour when pressed to theme colour
    void setPressedBackgroundColour(SGXColourRGBA customColour); // set background colour when pressed to custom colour
    void setPressedForegroundColour(); // set handle colour when pressed to default colour
    void setPressedForegroundColour(int themeColourIndex); // set handle colour when pressed to theme colour
    void setPressedForegroundColour(SGXColourRGBA customColour); // set handle colour when pressed to custom colour
    void enterEvent(QEnterEvent*) override; // NOLINT(readability-named-parameter)
    void leaveEvent(QEvent*) override; // NOLINT(readability-named-parameter)
    void mousePressEvent(QMouseEvent* event) override; // updates scroll bar appearance when pressed
    void mouseReleaseEvent(QMouseEvent* event) override; // updates scroll bar appearance when released
    void paintEvent(QPaintEvent*) override; // NOLINT(readability-named-parameter);
    // resize in parent SGXScrollView
};

#endif // SGXSCROLLBAR_H
