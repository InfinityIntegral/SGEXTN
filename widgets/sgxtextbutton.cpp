#include "sgxtextbutton.h"
#include "../userDefinedClasses/sgucentralmanagement.h"
#include "../misc/sgxcentral.h"
#include <QPainter>
#include <QWidget>
#include "../userDefinedClasses/sgusignalemitter.h"
#include <QString>
#include "../primitives/sgxcolourrgba.h"
#include <QPaintEvent>
#include <QColor>
#include <QtCore/Qt>
#include <QEvent>
#include <QPushButton>

SGXTextButton::SGXTextButton(QWidget *parent, void (SGUSignalEmitter::*resizeSignal)(), const QString &s, void (*attachedFunction)(), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0){
    (*this).setParent(parent);
    (*this).x1 = x1;
    (*this).x0 = x0;
    (*this).y1 = y1;
    (*this).y0 = y0;
    (*this).w1 = w1;
    (*this).w0 = w0;
    (*this).h1 = h1;
    (*this).h0 = h0;
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
    (*this).font = (*SGXCentral::standardFont);
    (*this).unselected = false;
    (*this).pressed = false;
    (*this).hovering = false;
    (*this).show();
    connect(SGXCentral::signalEmitter, resizeSignal, this, &SGXTextButton::resizeObject);
    connect(this, &SGXTextButton::clicked, attachedFunction);
    (*this).resizeObject();
}

void SGXTextButton::setText(const QString& s){
    (*this).s = s;
    (*this).update();
}

void SGXTextButton::setBackgroundColour(){
    backgroundColour = SGUCentralManagement::buttonBackgroundColour.getQColour();
    update();
}

void SGXTextButton::setBackgroundColour(int themeColourIndex){
    backgroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::buttonBackgroundColour);
    update();
}

void SGXTextButton::setBackgroundColour(SGXColourRGBA customColour){
    backgroundColour = customColour.getQColour();
    update();
}

void SGXTextButton::setForegroundColour(){
    foregroundColour = SGUCentralManagement::buttonForegroundColour.getQColour();
    update();
}

void SGXTextButton::setForegroundColour(int themeColourIndex){
    foregroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::buttonForegroundColour);
    update();
}

void SGXTextButton::setForegroundColour(SGXColourRGBA customColour){
    foregroundColour = customColour.getQColour();
    update();
}

void SGXTextButton::setHoverBackgroundColour(){
    hoverBackgroundColour = SGUCentralManagement::buttonHoverBackgroundColour.getQColour();
    update();
}

void SGXTextButton::setHoverBackgroundColour(int themeColourIndex){
    hoverBackgroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::buttonHoverBackgroundColour);
    update();
}

void SGXTextButton::setHoverBackgroundColour(SGXColourRGBA customColour){
    hoverBackgroundColour = customColour.getQColour();
    update();
}

void SGXTextButton::setHoverForegroundColour(){
    hoverForegroundColour = SGUCentralManagement::buttonHoverForegroundColour.getQColour();
    update();
}

void SGXTextButton::setHoverForegroundColour(int themeColourIndex){
    hoverForegroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::buttonHoverForegroundColour);
    update();
}

void SGXTextButton::setHoverForegroundColour(SGXColourRGBA customColour){
    hoverForegroundColour = customColour.getQColour();
    update();
}

void SGXTextButton::setPressedBackgroundColour(){
    pressedBackgroundColour = SGUCentralManagement::buttonPressedBackgroundColour.getQColour();
    update();
}

void SGXTextButton::setPressedBackgroundColour(int themeColourIndex){
    pressedBackgroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::buttonPressedBackgroundColour);
    update();
}

void SGXTextButton::setPressedBackgroundColour(SGXColourRGBA customColour){
    pressedBackgroundColour = customColour.getQColour();
    update();
}

void SGXTextButton::setPressedForegroundColour(){
    pressedForegroundColour = SGUCentralManagement::buttonPressedForegroundColour.getQColour();
    update();
}

void SGXTextButton::setPressedForegroundColour(int themeColourIndex){
    pressedForegroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::buttonPressedForegroundColour);
    update();
}

void SGXTextButton::setPressedForegroundColour(SGXColourRGBA customColour){
    pressedForegroundColour = customColour.getQColour();
    update();
}

void SGXTextButton::setUnselectedBackgroundColour(){
    unselectedBackgroundColour = SGUCentralManagement::unselectedButtonBackgroundColour.getQColour();
    update();
}

void SGXTextButton::setUnselectedBackgroundColour(int themeColourIndex){
    unselectedBackgroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::unselectedButtonBackgroundColour);
    update();
}

void SGXTextButton::setUnselectedBackgroundColour(SGXColourRGBA customColour){
    unselectedBackgroundColour = customColour.getQColour();
    update();
}

void SGXTextButton::setUnselectedForegroundColour(){
    unselectedForegroundColour = SGUCentralManagement::unselectedButtonForegroundColour.getQColour();
    update();
}

void SGXTextButton::setUnselectedForegroundColour(int themeColourIndex){
    unselectedForegroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::unselectedButtonForegroundColour);
    update();
}

void SGXTextButton::setUnselectedForegroundColour(SGXColourRGBA customColour){
    unselectedForegroundColour = customColour.getQColour();
    update();
}

void SGXTextButton::setUnselectedHoverBackgroundColour(){
    (*this).unselectedHoverBackgroundColour = SGUCentralManagement::buttonHoverBackgroundColour.getQColour();
    update();
}

void SGXTextButton::setUnselectedHoverBackgroundColour(int themeColourIndex){
    (*this).unselectedHoverBackgroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::buttonHoverBackgroundColour);
    update();
}

void SGXTextButton::setUnselectedHoverBackgroundColour(SGXColourRGBA customColour){
    unselectedHoverBackgroundColour = customColour.getQColour();
    update();
}

void SGXTextButton::setUnselectedHoverForegroundColour(){
    unselectedHoverForegroundColour = SGUCentralManagement::buttonHoverForegroundColour.getQColour();
    update();
}

void SGXTextButton::setUnselectedHoverForegroundColour(int themeColourIndex){
    unselectedHoverForegroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::buttonHoverForegroundColour);
    update();
}

void SGXTextButton::setUnselectedHoverForegroundColour(SGXColourRGBA customColour){
    unselectedHoverForegroundColour = customColour.getQColour();
    update();
}

void SGXTextButton::resizeObject(){
    font.setPixelSize(static_cast<int>(h1 * SGXCentral::renderAreaHeight + h0 * SGXCentral::sizeUnit));
    setGeometry(static_cast<int>(x1 * SGXCentral::renderAreaWidth + x0 * SGXCentral::sizeUnit), static_cast<int>(y1 * SGXCentral::renderAreaHeight + y0 * SGXCentral::sizeUnit), static_cast<int>(w1 * SGXCentral::renderAreaWidth + w0 * SGXCentral::sizeUnit), static_cast<int>(h1 * SGXCentral::renderAreaHeight + h0 * SGXCentral::sizeUnit));
}

void SGXTextButton::enterEvent(QEnterEvent *){ // NOLINT(readability-named-parameter)
    hovering = true;
}

void SGXTextButton::leaveEvent(QEvent *){ // NOLINT(readability-named-parameter)
    hovering = false;
}

void SGXTextButton::mousePressEvent(QMouseEvent *event){
    pressed = true;
    QPushButton::mousePressEvent(event);
}

void SGXTextButton::mouseReleaseEvent(QMouseEvent *event){
    pressed = false;
    QPushButton::mouseReleaseEvent(event);
}

void SGXTextButton::paintEvent(QPaintEvent *){ // NOLINT(readability-named-parameter)
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
