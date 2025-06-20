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

SGXLongTextInternal::SGXLongTextInternal(SGXLongText *parent){
    (*this).setParent(parent);
    (*this).ref = parent;
    (*this).show();
}

void SGXLongTextInternal::paintEvent(QPaintEvent *){ // NOLINT(readability-named-parameter)
    const QFontMetrics fm((*ref).font);
    QList<int> lineGaps;
    int ls = 0;
    int lb = 0;
    const QString& s = (*ref).s;
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
            if(fm.horizontalAdvance(s.mid(lb, i - lb + 1)) > (*parentWidget()).width()){
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
    setGeometry(0, 0, (*parentWidget()).width(), static_cast<int>((*ref).font.pixelSize() * lineGaps.length() / 2));
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), (*ref).backgroundColour);
    p.setRenderHint(QPainter::TextAntialiasing);
    p.setFont((*ref).font);
    p.setPen((*ref).foregroundColour);
    for(int i=0; i<lineGaps.length()/2; i++){
        p.drawText(0, (*ref).font.pixelSize() * i, (*parentWidget()).width(), (*ref).font.pixelSize(), Qt::AlignLeft | Qt::AlignVCenter, s.mid(lineGaps[2 * static_cast<long long>(i)], lineGaps[2 * static_cast<long long>(i) + 1] - lineGaps[2 * static_cast<long long>(i)] + 1));
    }
}
