#include "sgxlayout.h"
#include "../misc/sgxcentral.h"
#include <QTimer>
#include <QPainter>
#include <QWidget>
#include "../userDefinedClasses/sgusignalemitter.h"
#include <QPaintEvent>

SGXLayout::SGXLayout(QWidget *parent, void (SGUSignalEmitter::*resizeSignal)()){
    (*this).setParent(parent);
    (*this).show();
    connect(SGXCentral::signalEmitter, resizeSignal, this, &SGXLayout::receiveUpdateCall);
    (*this).receiveUpdateCall();
}

void SGXLayout::receiveUpdateCall() const {
    QTimer::singleShot(0, this, &SGXLayout::resizeObject);
}

void SGXLayout::resizeObject(){
    const float w = static_cast<float>((*parentWidget()).width()) / SGXCentral::sizeUnit;
    float h = 0.0f;
    resizeComponents(w, h);
    setGeometry(0, 0, static_cast<int>(w * SGXCentral::sizeUnit), static_cast<int>(h * SGXCentral::sizeUnit));
}

void SGXLayout::paintEvent(QPaintEvent *){ // NOLINT(readability-named-parameter)
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), SGXCentral::noColour.getQColour());
}
