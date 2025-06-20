#include "sgxlongtext.h"
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
#include "../widgets/sgxlongtextinternal.h"
#include <algorithm>

SGXLongText::SGXLongText(QWidget *parent, void (SGUSignalEmitter::*resizeSignal)(), const QString &s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float s1, float s0, float f1, float f0){
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
    (*this).backgroundColour = SGUCentralManagement::textBackgroundColour.getQColour();
    (*this).foregroundColour = SGUCentralManagement::textForegroundColour.getQColour();
    (*this).s = s;
    (*this).font = (*SGXCentral::standardFont);
    (*this).setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    (*this).setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    (*this).setFrameStyle(QFrame::NoFrame);
    SGXScrollBar* scrollBar = new SGXScrollBar(this); // NOLINT(cppcoreguidelines-owning-memory)
    setVerticalScrollBar(scrollBar);
    (*this).displayInternal = new SGXLongTextInternal(this); // NOLINT(cppcoreguidelines-owning-memory)
    (*this).setWidget((*this).displayInternal);
    (*this).show();
    connect(SGXCentral::signalEmitter, resizeSignal, this, &SGXLongText::resizeObject);
    (*this).resizeObject();
}

void SGXLongText::setText(const QString& s){
    (*this).s = s;
    (*this).update();
}

void SGXLongText::setBackgroundColour(){
    backgroundColour = SGUCentralManagement::textBackgroundColour.getQColour();
    update();
}

void SGXLongText::setBackgroundColour(int themeColourIndex){
    backgroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::textBackgroundColour);
    update();
}

void SGXLongText::setBackgroundColour(SGXColourRGBA customColour){
    backgroundColour = customColour.getQColour();
    update();
}

void SGXLongText::setForegroundColour(){
    foregroundColour = SGUCentralManagement::textForegroundColour.getQColour();
    update();
}

void SGXLongText::setForegroundColour(int themeColourIndex){
    foregroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::textForegroundColour);
    update();
}

void SGXLongText::setForegroundColour(SGXColourRGBA customColour){
    foregroundColour = customColour.getQColour();
    update();
}

void SGXLongText::resizeObject(){
    font.setPixelSize(static_cast<int>(f1 * SGXCentral::renderAreaHeight + f0 * SGXCentral::sizeUnit));
    setGeometry(static_cast<int>(x1 * SGXCentral::renderAreaWidth + x0 * SGXCentral::sizeUnit), static_cast<int>(y1 * SGXCentral::renderAreaHeight + y0 * SGXCentral::sizeUnit), static_cast<int>(w1 * SGXCentral::renderAreaWidth + w0 * SGXCentral::sizeUnit), static_cast<int>(h1 * SGXCentral::renderAreaHeight + h0 * SGXCentral::sizeUnit));
    (*verticalScrollBar()).setFixedWidth(static_cast<int>(s1 * SGXCentral::renderAreaWidth + s0 * SGXCentral::sizeUnit));
    splitLine();
}

void SGXLongText::splitLine(){
    const QFontMetrics fm(font);
    lineGaps = QList<int>();
    int ls = 0;
    int lb = 0;
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
}
