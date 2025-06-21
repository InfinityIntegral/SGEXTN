#include "sgxlonginputfieldinternal.h"
#include <QPainter>
#include <QWidget>
#include <QString>
#include <QPaintEvent>
#include <QtCore/Qt>
#include "../widgets/sgxlonginputfield.h"
#include <QTextCursor>
#include <QFrame>
#include <QColor>
#include <QTextEdit>
#include <QEvent>

SGXLongInputFieldInternal::SGXLongInputFieldInternal(SGXLongInputField *parent){
    (*this).setParent(parent);
    (*this).ref = parent;
    (*this).setFrameStyle(QFrame::NoFrame);
    connect(this, &SGXLongInputFieldInternal::textChanged, this, &SGXLongInputFieldInternal::refreshText);
    (*this).show();
}

void SGXLongInputFieldInternal::paintEvent(QPaintEvent *){ // NOLINT(readability-named-parameter)
    (*ref).cursorPosition = textCursor().position();
    (*ref).selectionRangeEnd = textCursor().anchor();
    // potential bug - after deleting selected text, selection may still show, update SGXInputField
    QPainter p(viewport());
    QColor bg;
    QColor fg;
    const QFontMetrics fm((*ref).font);
    if((*ref).invalid == true){
        bg = (*ref).invalidBackgroundColour;
        fg = (*ref).invalidForegroundColour;
    }
    else if((*ref).focused == true){
        bg = (*ref).focusedBackgroundColour;
        fg = (*ref).focusedForegroundColour;
    }
    else if((*ref).hovering == true){
        bg = (*ref).hoverBackgroundColour;
        fg = (*ref).hoverForegroundColour;
    }
    else{
        bg = (*ref).backgroundColour;
        fg = (*ref).foregroundColour;
    }
    const QString& s = toPlainText();
    p.fillRect(0, 0, (*viewport()).width(), (*viewport()).height(), bg);
    p.setRenderHint(QPainter::TextAntialiasing);
    p.setFont((*ref).font);
    int a = 0;
    int b = 0;
    if((*ref).cursorPosition < (*ref).selectionRangeEnd){
        a = (*ref).cursorPosition;
        b = (*ref).selectionRangeEnd;
    }
    else if((*ref).cursorPosition > (*ref).selectionRangeEnd){
        a = (*ref).selectionRangeEnd;
        b = (*ref).cursorPosition;
    }
    if(a == b){
        p.setPen(fg);
        for(int i=0; i<(*ref).lineGaps.length()/2; i++){
            p.drawText(0, (*ref).font.pixelSize() * i, (*parentWidget()).width(), (*ref).font.pixelSize(), Qt::AlignLeft | Qt::AlignVCenter, s.mid((*ref).lineGaps[2 * static_cast<long long>(i)], (*ref).lineGaps[2 * static_cast<long long>(i) + 1] - (*ref).lineGaps[2 * static_cast<long long>(i)] + 1));
        }
    }
    else{
        int la = 0;
        int lb = 0;
        int l = 0;
        int h = static_cast<int>((*ref).lineGaps.length()) / 2;
        while(h - l > 1){
            const int m = (l + h) / 2;
            if(a < (*ref).lineGaps[2 * static_cast<long long>(m)]){h = m;}
            else{l = m;}
        }
        la = l;
        l = 0;
        h = static_cast<int>((*ref).lineGaps.length()) / 2;
        while(h - l > 1){
            const int m = (l + h) / 2;
            if(b < (*ref).lineGaps[2 * static_cast<long long>(m)]){h = m;}
            else{l = m;}
        }
        lb = l;
        if(la == lb){
            p.setPen(fg);
            for(int i=0; i<la; i++){
                p.drawText(0, (*ref).font.pixelSize() * i, (*parentWidget()).width(), (*ref).font.pixelSize(), Qt::AlignLeft | Qt::AlignVCenter, s.mid((*ref).lineGaps[2 * static_cast<long long>(i)], (*ref).lineGaps[2 * static_cast<long long>(i) + 1] - (*ref).lineGaps[2 * static_cast<long long>(i)] + 1));
            }
            for(int i=la+1; i<(*ref).lineGaps.length() / 2; i++){
                p.drawText(0, (*ref).font.pixelSize() * i, (*parentWidget()).width(), (*ref).font.pixelSize(), Qt::AlignLeft | Qt::AlignVCenter, s.mid((*ref).lineGaps[2 * static_cast<long long>(i)], (*ref).lineGaps[2 * static_cast<long long>(i) + 1] - (*ref).lineGaps[2 * static_cast<long long>(i)] + 1));
            }
            p.setPen((*ref).selectionHighlightsForegroundColour);
            const QString sb = s.mid(a, b - a);
            const QString ub1 = s.mid((*ref).lineGaps[2 * static_cast<long long>(la)], a - (*ref).lineGaps[2 * static_cast<long long>(la)]);
            const QString ub2 = s.mid(b, (*ref).lineGaps[2 * la + 1] - b + 1);
            p.fillRect(fm.horizontalAdvance(ub1), (*ref).font.pixelSize() * la, fm.horizontalAdvance(sb), (*ref).font.pixelSize(), (*ref).selectionHighlightsBackgroundColour);
            p.drawText(fm.horizontalAdvance(ub1), (*ref).font.pixelSize() * la, fm.horizontalAdvance(sb), (*ref).font.pixelSize(), Qt::AlignLeft | Qt::AlignVCenter, sb);
            p.setPen(fg);
            p.drawText(0, (*ref).font.pixelSize() * la, fm.horizontalAdvance(ub1), (*ref).font.pixelSize(), Qt::AlignLeft | Qt::AlignVCenter, ub1);
            p.drawText(fm.horizontalAdvance(ub1) + fm.horizontalAdvance(sb), (*ref).font.pixelSize() * la, fm.horizontalAdvance(ub2), (*ref).font.pixelSize(), Qt::AlignLeft | Qt::AlignVCenter, ub2);
        }
        else{
            p.setPen(fg);
            for(int i=0; i<la; i++){
                p.drawText(0, (*ref).font.pixelSize() * i, (*parentWidget()).width(), (*ref).font.pixelSize(), Qt::AlignLeft | Qt::AlignVCenter, s.mid((*ref).lineGaps[2 * static_cast<long long>(i)], (*ref).lineGaps[2 * static_cast<long long>(i) + 1] - (*ref).lineGaps[2 * static_cast<long long>(i)] + 1));
            }
            {
                const QString ub = s.mid((*ref).lineGaps[2 * static_cast<long long>(la)], a - (*ref).lineGaps[2 * static_cast<long long>(la)]);
                const QString sb = s.mid(a, (*ref).lineGaps[2 * la + 1] - a + 1);
                p.drawText(0, (*ref).font.pixelSize() * la, fm.horizontalAdvance(ub), (*ref).font.pixelSize(), Qt::AlignLeft | Qt::AlignVCenter, ub);
                p.setPen((*ref).selectionHighlightsForegroundColour);
                p.fillRect(fm.horizontalAdvance(ub), (*ref).font.pixelSize() * la, fm.horizontalAdvance(sb), (*ref).font.pixelSize(), (*ref).selectionHighlightsBackgroundColour);
                p.drawText(fm.horizontalAdvance(ub), (*ref).font.pixelSize() * la, fm.horizontalAdvance(sb), (*ref).font.pixelSize(), Qt::AlignLeft | Qt::AlignVCenter, sb);
            }
            for(int i=la+1; i<lb; i++){
                p.fillRect(0, (*ref).font.pixelSize() * i, (*parentWidget()).width(), (*ref).font.pixelSize(), (*ref).selectionHighlightsBackgroundColour);
                p.drawText(0, (*ref).font.pixelSize() * i, (*parentWidget()).width(), (*ref).font.pixelSize(), Qt::AlignLeft | Qt::AlignVCenter, s.mid((*ref).lineGaps[2 * static_cast<long long>(i)], (*ref).lineGaps[2 * static_cast<long long>(i) + 1] - (*ref).lineGaps[2 * static_cast<long long>(i)] + 1));
            }
            {
                const QString sb = s.mid((*ref).lineGaps[2 * static_cast<long long>(lb)], b - (*ref).lineGaps[2 * static_cast<long long>(lb)]);
                const QString ub = s.mid(b, (*ref).lineGaps[2 * lb + 1] - b - 1);
                p.fillRect(0, (*ref).font.pixelSize() * lb, fm.horizontalAdvance(sb), (*ref).font.pixelSize(), (*ref).selectionHighlightsBackgroundColour);
                p.drawText(0, (*ref).font.pixelSize() * lb, fm.horizontalAdvance(sb), (*ref).font.pixelSize(), Qt::AlignLeft | Qt::AlignVCenter, sb);
                p.setPen(fg);
                p.drawText(fm.horizontalAdvance(sb), (*ref).font.pixelSize() * lb, fm.horizontalAdvance(ub), (*ref).font.pixelSize(), Qt::AlignLeft | Qt::AlignVCenter, ub);
            }
            for(int i=lb+1; i<(*ref).lineGaps.length() / 2; i++){
                p.drawText(0, (*ref).font.pixelSize() * i, (*parentWidget()).width(), (*ref).font.pixelSize(), Qt::AlignLeft | Qt::AlignVCenter, s.mid((*ref).lineGaps[2 * static_cast<long long>(i)], (*ref).lineGaps[2 * static_cast<long long>(i) + 1] - (*ref).lineGaps[2 * static_cast<long long>(i)] + 1));
            }
        }
    }
}

void SGXLongInputFieldInternal::enterEvent(QEnterEvent *){ // NOLINT(readability-named-parameter)
    (*ref).hovering = true;
}

void SGXLongInputFieldInternal::leaveEvent(QEvent *){ // NOLINT(readability-named-parameter)
    (*ref).hovering = false;
}

void SGXLongInputFieldInternal::focusInEvent(QFocusEvent *event){
    (*ref).focused = true;
    QTextEdit::focusInEvent(event);
}

void SGXLongInputFieldInternal::focusOutEvent(QFocusEvent *event){
    (*ref).focused = false;
    QTextEdit::focusOutEvent(event);
}

void SGXLongInputFieldInternal::mousePressEvent(QMouseEvent *event){
    QTextEdit::mousePressEvent(event);
    const int lineNumber = static_cast<int>(static_cast<float>((*event).pos().y()) / static_cast<float>((*ref).font.pixelSize()));
    if(lineNumber > (*ref).lineGaps.length() / 2 - 1){
        (*ref).cursorPosition = static_cast<int>(toPlainText().length());
        (*ref).selectionRangeEnd = (*ref).cursorPosition;
        QTextCursor tc = textCursor();
        tc.setPosition((*ref).cursorPosition);
        setTextCursor(tc);
        return;
    }
    const QString containedText = toPlainText().mid((*ref).lineGaps[2 * static_cast<long long>(lineNumber)], (*ref).lineGaps[2 * static_cast<long long>(lineNumber) + 1] - (*ref).lineGaps[2 * static_cast<long long>(lineNumber)] + 1);
    const QFontMetrics fm((*ref).font);
    const int posNow = (*event).pos().x();
    int l = 0;
    int h = static_cast<int>(containedText.length()) + 1;
    while(h - l > 1){
        const int m = (l + h) / 2;
        if((fm.horizontalAdvance(containedText.left(m)) + fm.horizontalAdvance(containedText.left(m - 1))) / 2 < posNow){l = m;}
        else{h = m;}
    }
    (*ref).cursorPosition = l + (*ref).lineGaps[2 * static_cast<long long>(lineNumber)];
    (*ref).selectionRangeEnd = (*ref).cursorPosition;
    QTextCursor tc = textCursor();
    tc.setPosition((*ref).cursorPosition);
    setTextCursor(tc);
    (*viewport()).update();
}

void SGXLongInputFieldInternal::mouseMoveEvent(QMouseEvent *event){
    if(static_cast<bool>((*event).buttons() & Qt::LeftButton) == false){return;}
    QTextEdit::mouseMoveEvent(event);
    const int lineNumber = static_cast<int>(static_cast<float>((*event).pos().y()) / static_cast<float>((*ref).font.pixelSize()));
    if(lineNumber > (*ref).lineGaps.length() / 2 - 1){
        (*ref).selectionRangeEnd = static_cast<int>(toPlainText().length());
        QTextCursor tc = textCursor();
        tc.setPosition((*ref).selectionRangeEnd, QTextCursor::KeepAnchor);
        setTextCursor(tc);
        return;
    }
    const QString containedText = toPlainText().mid((*ref).lineGaps[2 * static_cast<long long>(lineNumber)], (*ref).lineGaps[2 * static_cast<long long>(lineNumber) + 1] - (*ref).lineGaps[2 * static_cast<long long>(lineNumber)] + 1);
    const QFontMetrics fm((*ref).font);
    const int posNow = (*event).pos().x();
    int l = 0;
    int h = static_cast<int>(containedText.length()) + 1;
    while(h - l > 1){
        const int m = (l + h) / 2;
        if((fm.horizontalAdvance(containedText.left(m)) + fm.horizontalAdvance(containedText.left(m - 1))) / 2 < posNow){l = m;}
        else{h = m;}
    }
    (*ref).selectionRangeEnd = l + (*ref).lineGaps[2 * static_cast<long long>(lineNumber)];
    QTextCursor tc = textCursor();
    tc.setPosition((*ref).selectionRangeEnd, QTextCursor::KeepAnchor);
    setTextCursor(tc);
    (*viewport()).update();
}

void SGXLongInputFieldInternal::refreshText(){
    (*ref).splitLine();
    (*viewport()).update();
}
