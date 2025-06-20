#include "sgxinputfield.h"
#include "../userDefinedClasses/sgucentralmanagement.h"
#include "../misc/sgxcentral.h"
#include <QPainter>
#include <QWidget>
#include "../userDefinedClasses/sgusignalemitter.h"
#include <QString>
#include "./primitives/sgxcolourrgba.h"
#include <QPaintEvent>
#include <QColor>
#include <QtCore/Qt>
#include <QLineEdit>
#include <QEvent>
#include <QTimer>

SGXInputField::SGXInputField(QWidget *parent, void (SGUSignalEmitter::*resizeSignal)(), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0){
    (*this).setParent(parent);
    (*this).x1 = x1;
    (*this).x0 = x0;
    (*this).y1 = y1;
    (*this).y0 = y0;
    (*this).w1 = w1;
    (*this).w0 = w0;
    (*this).h1 = h1;
    (*this).h0 = h0;
    (*this).backgroundColour = SGUCentralManagement::inputFieldBackgroundColour.getQColour();
    (*this).foregroundColour = SGUCentralManagement::inputFieldForegroundColour.getQColour();
    (*this).hoverBackgroundColour = SGUCentralManagement::inputFieldHoverBackgroundColour.getQColour();
    (*this).hoverForegroundColour = SGUCentralManagement::inputFieldHoverForegroundColour.getQColour();
    (*this).focusedBackgroundColour = SGUCentralManagement::inputFieldFocusedBackgroundColour.getQColour();
    (*this).focusedForegroundColour = SGUCentralManagement::inputFieldFocusedForegroundColour.getQColour();
    (*this).selectionHighlightsBackgroundColour = SGUCentralManagement::inputFieldSelectedHighlightBackgroundColour.getQColour();
    (*this).selectionHighlightsForegroundColour = SGUCentralManagement::inputFieldSelectedHighlightForegroundColour.getQColour();
    (*this).invalidBackgroundColour = SGUCentralManagement::inputFieldInvalidBackgroundColour.getQColour();
    (*this).invalidForegroundColour = SGUCentralManagement::inputFieldInvalidForegroundColour.getQColour();
    (*this).font = (*SGXCentral::standardFont);
    (*this).setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    (*this).hovering = false;
    (*this).focused = false;
    (*this).invalid = false;
    (*this).focusJustStarted = false;
    (*this).cursorPosition = 0;
    (*this).selectionRangeEnd = 0;
    (*this).show();
    connect(SGXCentral::signalEmitter, resizeSignal, this, &SGXInputField::resizeObject);
    (*this).resizeObject();
}

void SGXInputField::setBackgroundColour(){
    backgroundColour = SGUCentralManagement::inputFieldBackgroundColour.getQColour();
    update();
}

void SGXInputField::setBackgroundColour(int themeColourIndex){
    backgroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::inputFieldBackgroundColour);
    update();
}

void SGXInputField::setBackgroundColour(SGXColourRGBA customColour){
    backgroundColour = customColour.getQColour();
    update();
}

void SGXInputField::setForegroundColour(){
    foregroundColour = SGUCentralManagement::inputFieldForegroundColour.getQColour();
    update();
}

void SGXInputField::setForegroundColour(int themeColourIndex){
    foregroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::inputFieldForegroundColour);
    update();
}

void SGXInputField::setForegroundColour(SGXColourRGBA customColour){
    foregroundColour = customColour.getQColour();
    update();
}

void SGXInputField::setHoverBackgroundColour(){
    hoverBackgroundColour = SGUCentralManagement::inputFieldHoverBackgroundColour.getQColour();
    update();
}

void SGXInputField::setHoverBackgroundColour(int themeColourIndex){
    hoverBackgroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::inputFieldHoverBackgroundColour);
    update();
}

void SGXInputField::setHoverBackgroundColour(SGXColourRGBA customColour){
    hoverBackgroundColour = customColour.getQColour();
    update();
}

void SGXInputField::setHoverForegroundColour(){
    hoverForegroundColour = SGUCentralManagement::inputFieldHoverForegroundColour.getQColour();
    update();
}

void SGXInputField::setHoverForegroundColour(int themeColourIndex){
    hoverForegroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::inputFieldHoverForegroundColour);
    update();
}

void SGXInputField::setHoverForegroundColour(SGXColourRGBA customColour){
    hoverForegroundColour = customColour.getQColour();
    update();
}

void SGXInputField::setFocusedBackgroundColour(){
    focusedBackgroundColour = SGUCentralManagement::inputFieldFocusedBackgroundColour.getQColour();
    update();
}

void SGXInputField::setFocusedBackgroundColour(int themeColourIndex){
    focusedBackgroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::inputFieldFocusedBackgroundColour);
    update();
}

void SGXInputField::setFocusedBackgroundColour(SGXColourRGBA customColour){
    focusedBackgroundColour = customColour.getQColour();
    update();
}

void SGXInputField::setFocusedForegroundColour(){
    focusedForegroundColour = SGUCentralManagement::inputFieldFocusedForegroundColour.getQColour();
    update();
}

void SGXInputField::setFocusedForegroundColour(int themeColourIndex){
    focusedForegroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::inputFieldFocusedForegroundColour);
    update();
}

void SGXInputField::setFocusedForegroundColour(SGXColourRGBA customColour){
    focusedForegroundColour = customColour.getQColour();
    update();
}

void SGXInputField::setSelectionHighlightsBackgroundColour(){
    selectionHighlightsBackgroundColour = SGUCentralManagement::inputFieldSelectedHighlightBackgroundColour.getQColour();
    update();
}

void SGXInputField::setSelectionHighlightsBackgroundColour(int themeColourIndex){
    selectionHighlightsBackgroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::inputFieldSelectedHighlightBackgroundColour);
    update();
}

void SGXInputField::setSelectionHighlightsBackgroundColour(SGXColourRGBA customColour){
    selectionHighlightsBackgroundColour = customColour.getQColour();
    update();
}

void SGXInputField::setSelectionHighlightsForegroundColour(){
    selectionHighlightsForegroundColour = SGUCentralManagement::inputFieldSelectedHighlightForegroundColour.getQColour();
    update();
}

void SGXInputField::setSelectionHighlightsForegroundColour(int themeColourIndex){
    selectionHighlightsForegroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::inputFieldSelectedHighlightForegroundColour);
    update();
}

void SGXInputField::setSelectionHighlightsForegroundColour(SGXColourRGBA customColour){
    selectionHighlightsForegroundColour = customColour.getQColour();
    update();
}

void SGXInputField::setInvalidBackgroundColour(){
    invalidBackgroundColour = SGUCentralManagement::inputFieldInvalidBackgroundColour.getQColour();
    update();
}

void SGXInputField::setInvalidBackgroundColour(int themeColourIndex){
    invalidBackgroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::inputFieldInvalidBackgroundColour);
    update();
}

void SGXInputField::setInvalidBackgroundColour(SGXColourRGBA customColour){
    invalidBackgroundColour = customColour.getQColour();
    update();
}

void SGXInputField::setInvalidForegroundColour(){
    invalidForegroundColour = SGUCentralManagement::inputFieldInvalidForegroundColour.getQColour();
    update();
}

void SGXInputField::setInvalidForegroundColour(int themeColourIndex){
    invalidForegroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::inputFieldInvalidForegroundColour);
    update();
}

void SGXInputField::setInvalidForegroundColour(SGXColourRGBA customColour){
    invalidForegroundColour = customColour.getQColour();
    update();
}

void SGXInputField::resizeObject(){
    font.setPixelSize(static_cast<int>(h1 * SGXCentral::renderAreaHeight + h0 * SGXCentral::sizeUnit));
    setGeometry(static_cast<int>(x1 * SGXCentral::renderAreaWidth + x0 * SGXCentral::sizeUnit), static_cast<int>(y1 * SGXCentral::renderAreaHeight + y0 * SGXCentral::sizeUnit), static_cast<int>(w1 * SGXCentral::renderAreaWidth + w0 * SGXCentral::sizeUnit), static_cast<int>(h1 * SGXCentral::renderAreaHeight + h0 * SGXCentral::sizeUnit));
}

void SGXInputField::enterEvent(QEnterEvent *){ // NOLINT(readability-named-parameter)
    hovering = true;
}

void SGXInputField::leaveEvent(QEvent *){ // NOLINT(readability-named-parameter)
    hovering = false;
}

void SGXInputField::focusInEvent(QFocusEvent *event){
    focused = true;
    focusJustStarted = true;
    QLineEdit::focusInEvent(event);
}

void SGXInputField::focusOutEvent(QFocusEvent *event){
    focused = false;
    QLineEdit::focusOutEvent(event);
}

void SGXInputField::mousePressEvent(QMouseEvent *event){
    QLineEdit::mousePressEvent(event);
    if(focusJustStarted == true){
        setCursorPosition(static_cast<int>(text().length()));
        setSelection(0, static_cast<int>(text().length()));
        focusJustStarted = false;
        return;
    }
    const QString containedText = text();
    const QFontMetrics fm(font);
    const int offset = static_cast<int>(0.5f * static_cast<float>(width() - fm.horizontalAdvance(containedText)));
    const int posNow = (*event).pos().x() - offset;
    int l = 0;
    int h = static_cast<int>(containedText.length()) + 1;
    while(h - l > 1){
        const int m = (l + h) / 2;
        if((fm.horizontalAdvance(containedText.left(m)) + fm.horizontalAdvance(containedText.left(m - 1))) / 2 < posNow){l = m;}
        else{h = m;}
    }
    cursorPosition = l;
    setCursorPosition(cursorPosition);
    setSelection(cursorPosition, 0);
}

void SGXInputField::mouseMoveEvent(QMouseEvent *event){
    if(static_cast<bool>((*event).buttons() & Qt::LeftButton) == false){return;}
    QLineEdit::mouseMoveEvent(event);
    const QString containedText = text();
    const QFontMetrics fm(font);
    const int offset = static_cast<int>(0.5f * static_cast<float>(width() - fm.horizontalAdvance(containedText)));
    const int posNow = (*event).pos().x() - offset;
    int l = 0;
    int h = static_cast<int>(containedText.length()) + 1;
    while(h - l > 1){
        const int m = (l + h) / 2;
        if((fm.horizontalAdvance(containedText.left(m)) + fm.horizontalAdvance(containedText.left(m - 1))) / 2 < posNow){l = m;}
        else{h = m;}
    }
    selectionRangeEnd = l;
    setCursorPosition(cursorPosition);
    if(selectionRangeEnd > cursorPosition){setSelection(cursorPosition, selectionRangeEnd - cursorPosition);}
    else{setSelection(selectionRangeEnd, cursorPosition - selectionRangeEnd);}
}

void SGXInputField::paintEvent(QPaintEvent *){ // NOLINT(readability-named-parameter)
    QPainter p(this);
    QColor bg;
    QColor fg;
    if(invalid == true){
        bg = invalidBackgroundColour;
        fg = invalidForegroundColour;
    }
    else if(focused == true){
        bg = focusedBackgroundColour;
        fg = focusedForegroundColour;
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
    const int t0 = static_cast<int>(selectionStart());
    const int t1 = static_cast<int>(t0 + selectedText().length());
    if(focused == false || t0 == t1){
        p.setRenderHint(QPainter::TextAntialiasing);
        p.setFont(font);
        p.setPen(fg);
        p.drawText(0, 0, width(), height(), Qt::AlignHCenter | Qt::AlignVCenter, text());
    }
    else{
        const QString unselectedBlock1 = text().left(t0);
        const QString unselectedBlock2 = text().right(text().length() - t1);
        const QString selectedBlock = selectedText();
        const QFontMetrics fm(font);
        const int ub1 = fm.horizontalAdvance(unselectedBlock1);
        const int ub2 = fm.horizontalAdvance(unselectedBlock2);
        const int sb = fm.horizontalAdvance(selectedBlock);
        const int offset = static_cast<int>(0.5f * static_cast<float>(width() - ub1 - sb - ub2));
        p.fillRect(offset + ub1, 0, sb, height(), selectionHighlightsBackgroundColour);
        p.setRenderHint(QPainter::TextAntialiasing);
        p.setFont(font);
        p.setPen(fg);
        p.drawText(offset, 0, ub1, height(), Qt::AlignLeft | Qt::AlignVCenter, unselectedBlock1);
        p.drawText(offset + ub1 + sb, 0, ub2, height(), Qt::AlignLeft | Qt::AlignVCenter, unselectedBlock2);
        p.setPen(selectionHighlightsForegroundColour);
        p.drawText(offset + ub1, 0, sb, height(), Qt::AlignLeft | Qt::AlignVCenter, selectedBlock);
    }
}

void SGXInputField::setInput(const QString &s){
    setText(s);
    cursorPosition = static_cast<int>(s.length());
    selectionRangeEnd = static_cast<int>(s.length());
    setCursorPosition(static_cast<int>(s.length()));
    setSelection(static_cast<int>(s.length()), 0);
}

QString SGXInputField::getInput(){
    return text();
}

int SGXInputField::getInputAsInt(bool &can){
    return text().toInt(&can);
}

float SGXInputField::getInputAsFloat(bool &can){
    return text().toFloat(&can);
}

void SGXInputField::setInvalid(const QString &s){
    (*this).setText(s);
    invalid = true;
    QTimer::singleShot(1000, this, &SGXInputField::unsetInvalid);
    update();
}

void SGXInputField::unsetInvalid(){
    invalid = false;
    update();
}
