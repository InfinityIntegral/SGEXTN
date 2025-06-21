#include "sgxlonginputfield.h"
#include "../userDefinedClasses/sgucentralmanagement.h"
#include "../misc/sgxcentral.h"
#include "../widgets/sgxscrollbar.h"
#include <QPainter>
#include <QWidget>
#include "../userDefinedClasses/sgusignalemitter.h"
#include <QString>
#include <QtCore/Qt>
#include <QFrame>
#include "../primitives/sgxcolourrgba.h"
#include <QList>
#include "../widgets/sgxlonginputfieldinternal.h"
#include <algorithm>
#include <QTextCursor>
#include <QTimer>

SGXLongInputField::SGXLongInputField(QWidget *parent, void (SGUSignalEmitter::*resizeSignal)(), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float s1, float s0, float f1, float f0){
    (*this).setParent(parent);
    (*this).x1 = x1;
    (*this).x0 = x0;
    (*this).y1 = y1;
    (*this).y0 = y0;
    (*this).w1 = w1;
    (*this).w0 = w0;
    (*this).h1 = h1;
    (*this).h0 = h0;
    (*this).s1 = s1;
    (*this).s0 = s0;
    (*this).f1 = f1;
    (*this).f0 = f0;
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
    (*this).cursorPosition = 0;
    (*this).selectionRangeEnd = 0;
    (*this).setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    (*this).setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    (*this).setFrameStyle(QFrame::NoFrame);
    SGXScrollBar* scrollBar = new SGXScrollBar(this); // NOLINT(cppcoreguidelines-owning-memory)
    setVerticalScrollBar(scrollBar);
    (*this).displayInternal = new SGXLongInputFieldInternal(this); // NOLINT(cppcoreguidelines-owning-memory)
    (*this).setWidget((*this).displayInternal);
    (*this).show();
    connect(SGXCentral::signalEmitter, resizeSignal, this, &SGXLongInputField::resizeObject);
    (*this).resizeObject();
}

void SGXLongInputField::setBackgroundColour(SGXColourRGBA customColour){
    backgroundColour = customColour.getQColour();
    update();
}

void SGXLongInputField::setForegroundColour(){
    foregroundColour = SGUCentralManagement::inputFieldForegroundColour.getQColour();
    update();
}

void SGXLongInputField::setForegroundColour(int themeColourIndex){
    foregroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::inputFieldForegroundColour);
    update();
}

void SGXLongInputField::setForegroundColour(SGXColourRGBA customColour){
    foregroundColour = customColour.getQColour();
    update();
}

void SGXLongInputField::setHoverBackgroundColour(){
    hoverBackgroundColour = SGUCentralManagement::inputFieldHoverBackgroundColour.getQColour();
    update();
}

void SGXLongInputField::setHoverBackgroundColour(int themeColourIndex){
    hoverBackgroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::inputFieldHoverBackgroundColour);
    update();
}

void SGXLongInputField::setHoverBackgroundColour(SGXColourRGBA customColour){
    hoverBackgroundColour = customColour.getQColour();
    update();
}

void SGXLongInputField::setHoverForegroundColour(){
    hoverForegroundColour = SGUCentralManagement::inputFieldHoverForegroundColour.getQColour();
    update();
}

void SGXLongInputField::setHoverForegroundColour(int themeColourIndex){
    hoverForegroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::inputFieldHoverForegroundColour);
    update();
}

void SGXLongInputField::setHoverForegroundColour(SGXColourRGBA customColour){
    hoverForegroundColour = customColour.getQColour();
    update();
}

void SGXLongInputField::setFocusedBackgroundColour(){
    focusedBackgroundColour = SGUCentralManagement::inputFieldFocusedBackgroundColour.getQColour();
    update();
}

void SGXLongInputField::setFocusedBackgroundColour(int themeColourIndex){
    focusedBackgroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::inputFieldFocusedBackgroundColour);
    update();
}

void SGXLongInputField::setFocusedBackgroundColour(SGXColourRGBA customColour){
    focusedBackgroundColour = customColour.getQColour();
    update();
}

void SGXLongInputField::setFocusedForegroundColour(){
    focusedForegroundColour = SGUCentralManagement::inputFieldFocusedForegroundColour.getQColour();
    update();
}

void SGXLongInputField::setFocusedForegroundColour(int themeColourIndex){
    focusedForegroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::inputFieldFocusedForegroundColour);
    update();
}

void SGXLongInputField::setFocusedForegroundColour(SGXColourRGBA customColour){
    focusedForegroundColour = customColour.getQColour();
    update();
}

void SGXLongInputField::setSelectionHighlightsBackgroundColour(){
    selectionHighlightsBackgroundColour = SGUCentralManagement::inputFieldSelectedHighlightBackgroundColour.getQColour();
    update();
}

void SGXLongInputField::setSelectionHighlightsBackgroundColour(int themeColourIndex){
    selectionHighlightsBackgroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::inputFieldSelectedHighlightBackgroundColour);
    update();
}

void SGXLongInputField::setSelectionHighlightsBackgroundColour(SGXColourRGBA customColour){
    selectionHighlightsBackgroundColour = customColour.getQColour();
    update();
}

void SGXLongInputField::setSelectionHighlightsForegroundColour(){
    selectionHighlightsForegroundColour = SGUCentralManagement::inputFieldSelectedHighlightForegroundColour.getQColour();
    update();
}

void SGXLongInputField::setSelectionHighlightsForegroundColour(int themeColourIndex){
    selectionHighlightsForegroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::inputFieldSelectedHighlightForegroundColour);
    update();
}

void SGXLongInputField::setSelectionHighlightsForegroundColour(SGXColourRGBA customColour){
    selectionHighlightsForegroundColour = customColour.getQColour();
    update();
}

void SGXLongInputField::setInvalidBackgroundColour(){
    invalidBackgroundColour = SGUCentralManagement::inputFieldInvalidBackgroundColour.getQColour();
    update();
}

void SGXLongInputField::setInvalidBackgroundColour(int themeColourIndex){
    invalidBackgroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::inputFieldInvalidBackgroundColour);
    update();
}

void SGXLongInputField::setInvalidBackgroundColour(SGXColourRGBA customColour){
    invalidBackgroundColour = customColour.getQColour();
    update();
}

void SGXLongInputField::setInvalidForegroundColour(){
    invalidForegroundColour = SGUCentralManagement::inputFieldInvalidForegroundColour.getQColour();
    update();
}

void SGXLongInputField::setInvalidForegroundColour(int themeColourIndex){
    invalidForegroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::inputFieldInvalidForegroundColour);
    update();
}

void SGXLongInputField::setInvalidForegroundColour(SGXColourRGBA customColour){
    invalidForegroundColour = customColour.getQColour();
    update();
}

void SGXLongInputField::setInput(const QString &s){
    (*displayInternal).setText(s);
    cursorPosition = static_cast<int>(s.length());
    selectionRangeEnd = static_cast<int>(s.length());
    QTextCursor tc = (*displayInternal).textCursor();
    tc.setPosition(static_cast<int>(s.length()));
    (*displayInternal).setTextCursor(tc);
}

QString SGXLongInputField::getInput() const {
    return (*displayInternal).toPlainText();
}

void SGXLongInputField::setInvalid(const QString &s){
    (*displayInternal).setText(s);
    invalid = true;
    QTimer::singleShot(1000, this, &SGXLongInputField::unsetInvalid);
    update();
}

void SGXLongInputField::unsetInvalid(){
    invalid = false;
    update();
}

void SGXLongInputField::resizeObject(){
    font.setPixelSize(static_cast<int>(f1 * SGXCentral::renderAreaHeight + f0 * SGXCentral::sizeUnit));
    setGeometry(static_cast<int>(x1 * SGXCentral::renderAreaWidth + x0 * SGXCentral::sizeUnit), static_cast<int>(y1 * SGXCentral::renderAreaHeight + y0 * SGXCentral::sizeUnit), static_cast<int>(w1 * SGXCentral::renderAreaWidth + w0 * SGXCentral::sizeUnit), static_cast<int>(h1 * SGXCentral::renderAreaHeight + h0 * SGXCentral::sizeUnit));
    (*verticalScrollBar()).setFixedWidth(static_cast<int>(s1 * SGXCentral::renderAreaWidth + s0 * SGXCentral::sizeUnit));
    splitLine();
}

void SGXLongInputField::splitLine(){
    const QFontMetrics fm(font);
    lineGaps = QList<int>();
    int ls = 0;
    int lb = 0;
    const QString& s = (*displayInternal).toPlainText();
    const int viewportWidth = (*viewport()).width();
    for(int i=0; i<s.length(); i++){
        if(s[i] == ' ' || s[i] == '\t'){
            ls = i;
        }
        else if(s[i] == '\n'){
            lineGaps.append(lb);
            lineGaps.append(i - 1);
            ls = i;
            lb = i + 1;
        }
        else{
            if(fm.horizontalAdvance(s.mid(lb, i - lb + 1)) > viewportWidth){
                if(lb < ls){
                    lineGaps.append(lb);
                    lineGaps.append(ls - 1);
                    lb = ls + 1;
                }
                else{
                    lineGaps.append(lb);
                    lineGaps.append(i-1);
                    ls = i - 1;
                    lb = i;
                }
            }
        }
    }
    lineGaps.append(lb);
    lineGaps.append(static_cast<int>(s.length() - 1));
    (*displayInternal).setGeometry(0, 0, viewportWidth, std::max((*viewport()).height(), static_cast<int>(font.pixelSize() * lineGaps.length() / 2)));
    (*(*displayInternal).viewport()).setGeometry(0, 0, (*displayInternal).width() + 1, (*displayInternal).height() + 1);
}
