#include "sgxlongtextinternal.h"
#include <QPainter>
#include <QWidget>
#include <QString>
#include <QPaintEvent>
#include <QList>
#include <QtCore/Qt>
#include "../widgets/sgxlongtext.h"

SGXLongTextInternal::SGXLongTextInternal(SGXLongText *parent){
    (*this).setParent(parent);
    (*this).ref = parent;
    (*this).show();
}

void SGXLongTextInternal::paintEvent(QPaintEvent *){ // NOLINT(readability-named-parameter)
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), (*ref).backgroundColour);
    p.setRenderHint(QPainter::TextAntialiasing);
    p.setFont((*ref).font);
    p.setPen((*ref).foregroundColour);
    for(int i=0; i<(*ref).lineGaps.length()/2; i++){
        p.drawText(0, (*ref).font.pixelSize() * i, (*parentWidget()).width(), (*ref).font.pixelSize(), Qt::AlignLeft | Qt::AlignVCenter, (*ref).s.mid((*ref).lineGaps[2 * static_cast<long long>(i)], (*ref).lineGaps[2 * static_cast<long long>(i) + 1] - (*ref).lineGaps[2 * static_cast<long long>(i)] + 1));
    }
}
