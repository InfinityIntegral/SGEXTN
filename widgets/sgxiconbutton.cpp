#include "sgxiconbutton.h"
#include "../userDefinedClasses/sgucentralmanagement.h"
#include "../misc/sgxcentral.h"
#include <QPainter>
#include <QWidget>
#include "../userDefinedClasses/sgusignalemitter.h"
#include <QChar>
#include "../primitives/sgxcolourrgba.h"
#include <QPaintEvent>
#include <QColor>
#include <QtCore/Qt>
#include <QEvent>
#include <QPushButton>

SGXIconButton::SGXIconButton(QWidget *parent, void (SGUSignalEmitter::*resizeSignal)(), const QChar &s, void (*attachedFunction)(), float x1, float x0, float y1, float y0, float w1, float w0){
    (*this).setParent(parent);
    (*this).x1 = x1;
    (*this).x0 = x0;
    (*this).y1 = y1;
    (*this).y0 = y0;
    (*this).w1 = w1;
    (*this).w0 = w0;
    (*this).backgroundColour = SGUCentralManagement::buttonBackgroundColour.getQColour();
    (*this).foregroundColour = SGUCentralManagement::buttonForegroundColour.getQColour();
    (*this).hoverBackgroundColour = SGUCentralManagement::buttonHoverBackgroundColour.getQColour();
    (*this).hoverForegroundColour = SGUCentralManagement::buttonHoverForegroundColour.getQColour();
    (*this).pressedBackgroundColour = SGUCentralManagement::buttonPressedBackgroundColour.getQColour();
    (*this).pressedForegroundColour = SGUCentralManagement::buttonPressedForegroundColour.getQColour();
    (*this).unselectedBackgroundColour = SGUCentralManagement::unselectedButtonBackgroundColour.getQColour();
    (*this).unselectedForegroundColour = SGUCentralManagement::unselectedButtonForegroundColour.getQColour();
    (*this).unselectedHoverBackgroundColour = SGUCentralManagement::unselectedButtonHoverBackgroundColour.getQColour();
    (*this).unselectedHoverForegroundColour = SGUCentralManagement::unselectedButtonHoverForegroundColour.getQColour();
    (*this).s = s;
    (*this).font = (*SGXCentral::iconsFont);
    (*this).unselected = false;
    (*this).pressed = false;
    (*this).hovering = false;
    (*this).show();
    connect(SGXCentral::signalEmitter, resizeSignal, this, &SGXIconButton::resizeObject);
    connect(this, &SGXIconButton::clicked, attachedFunction);
    (*this).resizeObject();
}

void SGXIconButton::setText(const QChar &s){
    (*this).s = s;
    (*this).update();
}

void SGXIconButton::setBackgroundColour(){
    backgroundColour = SGUCentralManagement::buttonBackgroundColour.getQColour();
    update();
}

void SGXIconButton::setBackgroundColour(int themeColourIndex){
    backgroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::buttonBackgroundColour);
    update();
}

void SGXIconButton::setBackgroundColour(SGXColourRGBA customColour){
    backgroundColour = customColour.getQColour();
    update();
}

void SGXIconButton::setForegroundColour(){
    foregroundColour = SGUCentralManagement::buttonForegroundColour.getQColour();
    update();
}

void SGXIconButton::setForegroundColour(int themeColourIndex){
    foregroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::buttonForegroundColour);
    update();
}

void SGXIconButton::setForegroundColour(SGXColourRGBA customColour){
    foregroundColour = customColour.getQColour();
    update();
}

void SGXIconButton::setHoverBackgroundColour(){
    hoverBackgroundColour = SGUCentralManagement::buttonHoverBackgroundColour.getQColour();
    update();
}

void SGXIconButton::setHoverBackgroundColour(int themeColourIndex){
    hoverBackgroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::buttonHoverBackgroundColour);
    update();
}

void SGXIconButton::setHoverBackgroundColour(SGXColourRGBA customColour){
    hoverBackgroundColour = customColour.getQColour();
    update();
}

void SGXIconButton::setHoverForegroundColour(){
    hoverForegroundColour = SGUCentralManagement::buttonHoverForegroundColour.getQColour();
    update();
}

void SGXIconButton::setHoverForegroundColour(int themeColourIndex){
    hoverForegroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::buttonHoverForegroundColour);
    update();
}

void SGXIconButton::setHoverForegroundColour(SGXColourRGBA customColour){
    hoverForegroundColour = customColour.getQColour();
    update();
}

void SGXIconButton::setPressedBackgroundColour(){
    pressedBackgroundColour = SGUCentralManagement::buttonPressedBackgroundColour.getQColour();
    update();
}

void SGXIconButton::setPressedBackgroundColour(int themeColourIndex){
    pressedBackgroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::buttonPressedBackgroundColour);
    update();
}

void SGXIconButton::setPressedBackgroundColour(SGXColourRGBA customColour){
    pressedBackgroundColour = customColour.getQColour();
    update();
}

void SGXIconButton::setPressedForegroundColour(){
    pressedForegroundColour = SGUCentralManagement::buttonPressedForegroundColour.getQColour();
    update();
}

void SGXIconButton::setPressedForegroundColour(int themeColourIndex){
    pressedForegroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::buttonPressedForegroundColour);
    update();
}

void SGXIconButton::setPressedForegroundColour(SGXColourRGBA customColour){
    pressedForegroundColour = customColour.getQColour();
    update();
}

void SGXIconButton::setUnselectedBackgroundColour(){
    unselectedBackgroundColour = SGUCentralManagement::unselectedButtonBackgroundColour.getQColour();
    update();
}

void SGXIconButton::setUnselectedBackgroundColour(int themeColourIndex){
    unselectedBackgroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::unselectedButtonBackgroundColour);
    update();
}

void SGXIconButton::setUnselectedBackgroundColour(SGXColourRGBA customColour){
    unselectedBackgroundColour = customColour.getQColour();
    update();
}

void SGXIconButton::setUnselectedForegroundColour(){
    unselectedForegroundColour = SGUCentralManagement::unselectedButtonForegroundColour.getQColour();
    update();
}

void SGXIconButton::setUnselectedForegroundColour(int themeColourIndex){
    unselectedForegroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::unselectedButtonForegroundColour);
    update();
}

void SGXIconButton::setUnselectedForegroundColour(SGXColourRGBA customColour){
    unselectedForegroundColour = customColour.getQColour();
    update();
}

void SGXIconButton::setUnselectedHoverBackgroundColour(){
    (*this).unselectedHoverBackgroundColour = SGUCentralManagement::buttonHoverBackgroundColour.getQColour();
    update();
}

void SGXIconButton::setUnselectedHoverBackgroundColour(int themeColourIndex){
    (*this).unselectedHoverBackgroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::buttonHoverBackgroundColour);
    update();
}

void SGXIconButton::setUnselectedHoverBackgroundColour(SGXColourRGBA customColour){
    unselectedHoverBackgroundColour = customColour.getQColour();
    update();
}

void SGXIconButton::setUnselectedHoverForegroundColour(){
    unselectedHoverForegroundColour = SGUCentralManagement::buttonHoverForegroundColour.getQColour();
    update();
}

void SGXIconButton::setUnselectedHoverForegroundColour(int themeColourIndex){
    unselectedHoverForegroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::buttonHoverForegroundColour);
    update();
}

void SGXIconButton::setUnselectedHoverForegroundColour(SGXColourRGBA customColour){
    unselectedHoverForegroundColour = customColour.getQColour();
    update();
}

void SGXIconButton::resizeObject(){
    font.setPixelSize(static_cast<int>(w1 * SGXCentral::renderAreaHeight + w0 * SGXCentral::sizeUnit));
    setGeometry(static_cast<int>(x1 * SGXCentral::renderAreaWidth + x0 * SGXCentral::sizeUnit), static_cast<int>(y1 * SGXCentral::renderAreaHeight + y0 * SGXCentral::sizeUnit), static_cast<int>(w1 * SGXCentral::renderAreaWidth + w0 * SGXCentral::sizeUnit), static_cast<int>(w1 * SGXCentral::renderAreaHeight + w0 * SGXCentral::sizeUnit));
}

void SGXIconButton::enterEvent(QEnterEvent *){ // NOLINT(readability-named-parameter)
    hovering = true;
}

void SGXIconButton::leaveEvent(QEvent *){ // NOLINT(readability-named-parameter)
    hovering = false;
}

void SGXIconButton::mousePressEvent(QMouseEvent *event){
    pressed = true;
    QPushButton::mousePressEvent(event);
}

void SGXIconButton::mouseReleaseEvent(QMouseEvent *event){
    pressed = false;
    QPushButton::mouseReleaseEvent(event);
}

void SGXIconButton::paintEvent(QPaintEvent *){ // NOLINT(readability-named-parameter)
    QPainter p(this);
    QColor bg;
    QColor fg;
    if(pressed == true){
        bg = pressedBackgroundColour;
        fg = pressedForegroundColour;
    }
    else if(unselected == true){
        if(hovering == true){
            bg = unselectedHoverBackgroundColour;
            fg = unselectedHoverForegroundColour;
        }
        else{
            bg = unselectedBackgroundColour;
            fg = unselectedForegroundColour;
        }
    }
    else{
        if(hovering == true){
            bg = hoverBackgroundColour;
            fg = hoverForegroundColour;
        }
        else{
            bg = backgroundColour;
            fg = foregroundColour;
        }
    }
    p.fillRect(0, 0, width(), height(), bg);
    p.setRenderHint(QPainter::TextAntialiasing);
    p.setFont(font);
    p.setPen(fg);
    p.drawText(0, 0, width(), height(), Qt::AlignHCenter | Qt::AlignVCenter, s);
}
