#include "sgxscrollbar.h"
#include "../userDefinedClasses/sgucentralmanagement.h"
#include "../misc/sgxcentral.h"
#include <QPainter>
#include <QWidget>
#include "../primitives/sgxcolourrgba.h"
#include <QPaintEvent>
#include <QColor>
#include <QEvent>
#include <QScrollBar>

SGXScrollBar::SGXScrollBar(QWidget *parent, float w1, float w0){
    (*this).setParent(parent);
    (*this).w1 = w1;
    (*this).w0 = w0;
    (*this).backgroundColour = SGUCentralManagement::scrollBarBackgroundColour.getQColour();
    (*this).foregroundColour = SGUCentralManagement::scrollBarForegroundColour.getQColour();
    (*this).hoverBackgroundColour = SGUCentralManagement::scrollBarHoverBackgroundColour.getQColour();
    (*this).hoverForegroundColour = SGUCentralManagement::scrollBarHoverForegroundColour.getQColour();
    (*this).pressedBackgroundColour = SGUCentralManagement::scrollBarPressedBackgroundColour.getQColour();
    (*this).pressedForegroundColour = SGUCentralManagement::scrollBarPressedForegroundColour.getQColour();
    (*this).hovering = false;
    (*this).pressed = false;
    (*this).show();
}

void SGXScrollBar::setBackgroundColour(){
    backgroundColour = SGUCentralManagement::scrollBarBackgroundColour.getQColour();
    update();
}

void SGXScrollBar::setBackgroundColour(int themeColourIndex){
    backgroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::scrollBarBackgroundColour);
    update();
}

void SGXScrollBar::setBackgroundColour(SGXColourRGBA customColour){
    backgroundColour = customColour.getQColour();
    update();
}

void SGXScrollBar::setForegroundColour(){
    foregroundColour = SGUCentralManagement::scrollBarForegroundColour.getQColour();
    update();
}

void SGXScrollBar::setForegroundColour(int themeColourIndex){
    foregroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::scrollBarForegroundColour);
    update();
}

void SGXScrollBar::setForegroundColour(SGXColourRGBA customColour){
    foregroundColour = customColour.getQColour();
    update();
}

void SGXScrollBar::setHoverBackgroundColour(){
    hoverBackgroundColour = SGUCentralManagement::scrollBarHoverBackgroundColour.getQColour();
    update();
}

void SGXScrollBar::setHoverBackgroundColour(int themeColourIndex){
    hoverBackgroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::scrollBarHoverBackgroundColour);
    update();
}

void SGXScrollBar::setHoverBackgroundColour(SGXColourRGBA customColour){
    hoverBackgroundColour = customColour.getQColour();
    update();
}

void SGXScrollBar::setHoverForegroundColour(){
    hoverForegroundColour = SGUCentralManagement::scrollBarHoverForegroundColour.getQColour();
    update();
}

void SGXScrollBar::setHoverForegroundColour(int themeColourIndex){
    hoverForegroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::scrollBarHoverForegroundColour);
    update();
}

void SGXScrollBar::setHoverForegroundColour(SGXColourRGBA customColour){
    hoverForegroundColour = customColour.getQColour();
    update();
}

void SGXScrollBar::setPressedBackgroundColour(){
    pressedBackgroundColour = SGUCentralManagement::scrollBarPressedBackgroundColour.getQColour();
    update();
}

void SGXScrollBar::setPressedBackgroundColour(int themeColourIndex){
    pressedBackgroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::scrollBarPressedBackgroundColour);
    update();
}

void SGXScrollBar::setPressedBackgroundColour(SGXColourRGBA customColour){
    pressedBackgroundColour = customColour.getQColour();
    update();
}

void SGXScrollBar::setPressedForegroundColour(){
    pressedForegroundColour = SGUCentralManagement::scrollBarPressedForegroundColour.getQColour();
    update();
}

void SGXScrollBar::setPressedForegroundColour(int themeColourIndex){
    pressedForegroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::scrollBarPressedForegroundColour);
    update();
}

void SGXScrollBar::setPressedForegroundColour(SGXColourRGBA customColour){
    pressedForegroundColour = customColour.getQColour();
    update();
}

void SGXScrollBar::enterEvent(QEnterEvent *){ // NOLINT(readability-named-parameter)
    hovering = true;
}

void SGXScrollBar::leaveEvent(QEvent *){ // NOLINT(readability-named-parameter)
    hovering = false;
}

void SGXScrollBar::mousePressEvent(QMouseEvent *event){
    pressed = true;
    QScrollBar::mousePressEvent(event);
}

void SGXScrollBar::mouseReleaseEvent(QMouseEvent *event){
    pressed = false;
    QScrollBar::mouseReleaseEvent(event);
}

void SGXScrollBar::paintEvent(QPaintEvent *){ // NOLINT(readability-named-parameter)
    QPainter p(this);
    QColor bg;
    QColor fg;
    if(pressed == true){
        bg = pressedBackgroundColour;
        fg = pressedForegroundColour;
    }
    else if(hovering == true){
        bg = hoverBackgroundColour;
        fg = hoverForegroundColour;
    }
    else{
        bg = backgroundColour;
        fg = foregroundColour;
    }
    p.fillRect(0, 0, width(), height(), bg);
    const float viewportHeightRelative = static_cast<float>(pageStep()) / static_cast<float>(maximum() + pageStep() - minimum());
    const float viewportPositionRelative = static_cast<float>(value()) / static_cast<float>(maximum() + pageStep() - minimum());
    p.fillRect(0, static_cast<int>(viewportPositionRelative * static_cast<float>(height())), width(), static_cast<int>(viewportHeightRelative * static_cast<float>(height())), fg);
}
