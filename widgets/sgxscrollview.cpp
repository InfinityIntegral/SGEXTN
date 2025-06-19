#include "sgxscrollview.h"
#include "sgxscrollbar.h"
#include "../misc/sgxcentral.h"
#include <QWidget>
#include "../userDefinedClasses/sgusignalemitter.h"
#include <QtCore/Qt>
#include <QFrame>

SGXScrollView::SGXScrollView(QWidget *parent, void (SGUSignalEmitter::*resizeSignal)(), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float s1, float s0){
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
    (*this).setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    (*this).setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    (*this).setFrameStyle(QFrame::NoFrame);
    SGXScrollBar* scrollBar = new SGXScrollBar(this); // NOLINT(cppcoreguidelines-owning-memory)
    setVerticalScrollBar(scrollBar);
    (*this).show();
    connect(SGXCentral::signalEmitter, resizeSignal, this, &SGXScrollView::resizeObject);
    (*this).resizeObject();
}

void SGXScrollView::resizeObject(){
    setGeometry(static_cast<int>(x1 * SGXCentral::renderAreaWidth + x0 * SGXCentral::sizeUnit), static_cast<int>(y1 * SGXCentral::renderAreaHeight + y0 * SGXCentral::sizeUnit), static_cast<int>(w1 * SGXCentral::renderAreaWidth + w0 * SGXCentral::sizeUnit), static_cast<int>(h1 * SGXCentral::renderAreaHeight + h0 * SGXCentral::sizeUnit));
    (*verticalScrollBar()).setFixedWidth(static_cast<int>(s1 * SGXCentral::renderAreaWidth + s0 * SGXCentral::sizeUnit));
}
