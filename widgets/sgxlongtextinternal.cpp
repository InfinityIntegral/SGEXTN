#include "sgxlongtextinternal.h"
#include "../userDefinedClasses/sgucentralmanagement.h"
#include "../misc/sgxcentral.h"
#include <QFontMetrics>
#include <QPainter>
#include <QWidget>
#include <QString>
#include "../primitives/sgxcolourrgba.h"
#include <QPaintEvent>
#include <QList>
#include <QtCore/Qt>

SGXLongTextInternal::SGXLongTextInternal(QWidget *parent){
    (*this).setParent(parent);
    (*this).backgroundColour = SGUCentralManagement::textBackgroundColour.getQColour();
    (*this).foregroundColour = SGUCentralManagement::textForegroundColour.getQColour();
    (*this).s = s;
    (*this).font = (*SGXCentral::standardFont);
    (*this).show();
}

void SGXLongTextInternal::setText(const QString &s){
    (*this).s = s;
    (*this).update();
}

void SGXLongTextInternal::setBackgroundColour(){
    backgroundColour = SGUCentralManagement::textBackgroundColour.getQColour();
    update();
}

void SGXLongTextInternal::setBackgroundColour(int themeColourIndex){
    backgroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::textBackgroundColour);
    update();
}

void SGXLongTextInternal::setBackgroundColour(SGXColourRGBA customColour){
    backgroundColour = customColour.getQColour();
    update();
}

void SGXLongTextInternal::setForegroundColour(){
    foregroundColour = SGUCentralManagement::textForegroundColour.getQColour();
    update();
}

void SGXLongTextInternal::setForegroundColour(int themeColourIndex){
    foregroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::textForegroundColour);
    update();
}

void SGXLongTextInternal::setForegroundColour(SGXColourRGBA customColour){
    foregroundColour = customColour.getQColour();
    update();
}

void SGXLongTextInternal::paintEvent(QPaintEvent *){ // NOLINT(readability-named-parameter)
    const QFontMetrics fm(font);
    QList<int> lineGaps;
    int ls = 0;
    int lb = 0;
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
            if(fm.horizontalAdvance(s.mid(lb, i - lb + 1)) > width()){
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
    setGeometry(0, 0, width(), static_cast<int>(font.pixelSize() * lineGaps.length() / 2));
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), backgroundColour);
    p.setRenderHint(QPainter::TextAntialiasing);
    p.setFont(font);
    p.setPen(foregroundColour);
    for(int i=0; i<lineGaps.length()/2; i++){
        p.drawText(0, font.pixelSize() * i, width(), font.pixelSize(), Qt::AlignLeft | Qt::AlignVCenter, s.mid(lineGaps[2 * static_cast<long long>(i)], lineGaps[2 * static_cast<long long>(i) + 1] - lineGaps[2 * static_cast<long long>(i)] + 1));
    }
}
