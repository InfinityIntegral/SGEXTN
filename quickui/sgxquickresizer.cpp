#include "sgxquickresizer.h"
#include "../quickui/sgxquickuiinterface.h"
#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>

SGXQuickResizer::SGXQuickResizer(){
    (*this).appWindowWidth = 0.0f;
    (*this).appWindowHeight = 0.0f;
}

QObject* SGXQuickResizer::getObject(QQmlEngine *me, QJSEngine *se){
    Q_UNUSED(me); // NOLINT
    Q_UNUSED(se); // NOLINT
    return new SGXQuickResizer();
}

float SGXQuickResizer::getAppWindowWidth() const {
    return (*this).appWindowWidth;
}

void SGXQuickResizer::setAppWindowWidth(float x){
    (*this).appWindowWidth = x;
    emit (*this).changedAppWindowWidth(); // NOLINT
}

float SGXQuickResizer::getAppWindowHeight() const {
    return (*this).appWindowHeight;
}

void SGXQuickResizer::setAppWindowHeight(float x){
    (*this).appWindowHeight = x;
    emit (*this).changedAppWindowHeight(); // NOLINT
}

void SGXQuickResizer::updateAppWindowSize(){
    setAppWindowWidth(static_cast<float>((*SGXQuickUIInterface::rootWindow).width()));
    setAppWindowHeight(static_cast<float>((*SGXQuickUIInterface::rootWindow).height()));
}
