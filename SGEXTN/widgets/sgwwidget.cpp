#include "sgwwidget.h"
#include "sgwtype.h"
#include <QSet>
#include <qcontainerfwd.h>
#include <QQuickItem>
#include <QObject>

SGWWidget* SGWWidget::rootWidget = nullptr;

SGWWidget::SGWWidget(SGWWidget* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0){
    (*this).type = SGWType::Undefined;
    (*this).parent = nullptr;
    (*this).children = QSet<SGWWidget*>();
    (*this).topObject = nullptr;
    (*this).bottomObject = nullptr;
    (*this).x1 = x1;
    (*this).x0 = x0;
    (*this).y1 = y1;
    (*this).y0 = y0;
    (*this).w1 = w1;
    (*this).w0 = w0;
    (*this).h1 = h1;
    (*this).h0 = h0;
    (*this).visible = true;
    (*this).parent = parent;
    if((*this).parent == nullptr){
        (*this).parentW1 = 1.0f;
        (*this).parentW0 = 0.0f;
        (*this).parentH1 = 1.0f;
        (*this).parentH0 = 0.0f;
    }
    else{
        (*this).parentW1 = (*(*this).parent).w1 * (*(*this).parent).parentW1;
        (*this).parentW0 = (*(*this).parent).w1 * (*(*this).parent).parentW0 + (*(*this).parent).w0;
        (*this).parentH1 = (*(*this).parent).h1 * (*(*this).parent).parentH1;
        (*this).parentH0 = (*(*this).parent).h1 * (*(*this).parent).parentH0 + (*(*this).parent).h0;
    }
}

SGWWidget::~SGWWidget(){
    if(parent != nullptr){(*parent).children.remove(this);}
    for(QSet<SGWWidget*>::iterator i = children.begin(); i != children.end(); i++){delete (*i);}
    delete topObject;
    QObject::~QObject();
}

SGWType::Type SGWWidget::getType() const {
    return type;
}

SGWWidget* SGWWidget::getParent() const {
    return parent;
}

QVector<SGWWidget*> SGWWidget::getChildren() const {
    QVector<SGWWidget*> v = QVector<SGWWidget*>();
    for(QSet<SGWWidget*>::const_iterator i = children.begin(); i != children.end(); i++){
        v.push_back(*i);
    }
    return v;
}

QQuickItem* SGWWidget::getTopObject() const {
    return topObject;
}

QQuickItem* SGWWidget::getBottomObject() const {
    return bottomObject;
}

float SGWWidget::getX1() const {
    return x1;
}

void SGWWidget::setX1(float x1){
    (*this).x1 = x1;
    (*(*this).topObject).setProperty("x1", (*this).x1);
    updateSizeReferences();
}

float SGWWidget::getX0() const {
    return x0;
}

void SGWWidget::setX0(float x0){
    (*this).x0 = x0;
    (*(*this).topObject).setProperty("x0", (*this).x0);
    updateSizeReferences();
}

float SGWWidget::getY1() const {
    return y1;
}

void SGWWidget::setY1(float y1){
    (*this).y1 = y1;
    (*(*this).topObject).setProperty("y1", (*this).y1);
    updateSizeReferences();
}

float SGWWidget::getY0() const {
    return y0;
}

void SGWWidget::setY0(float y0){
    (*this).y0 = y0;
    (*(*this).topObject).setProperty("y0", (*this).y0);
    updateSizeReferences();
}

float SGWWidget::getW1() const {
    return w1;
}

void SGWWidget::setW1(float w1){
    (*this).w1 = w1;
    (*(*this).topObject).setProperty("w1", (*this).w1);
    updateSizeReferences();
}

float SGWWidget::getW0() const {
    return w0;
}

void SGWWidget::setW0(float w0){
    (*this).w0 = w0;
    (*(*this).topObject).setProperty("w0", (*this).w0);
    updateSizeReferences();
}

float SGWWidget::getH1() const {
    return h1;
}

void SGWWidget::setH1(float h1){
    (*this).h1 = h1;
    (*(*this).topObject).setProperty("h1", (*this).h1);
    updateSizeReferences();
}

float SGWWidget::getH0() const {
    return h0;
}

void SGWWidget::setH0(float h0){
    (*this).h0 = h0;
    (*(*this).topObject).setProperty("h0", (*this).h0);
    updateSizeReferences();
}

bool SGWWidget::getVisible() const {
    return visible;
}

float SGWWidget::getParentW1() const {
    return parentW1;
}

float SGWWidget::getParentW0() const {
    return parentW0;
}

float SGWWidget::getParentH1() const {
    return parentH1;
}

float SGWWidget::getParentH0() const {
    return parentH0;
}

void SGWWidget::updateSizeReferences(){ // NOLINT(misc-no-recursion)
    updateParentSize();
    const QVector<SGWWidget*> c = getChildren();
    for(int i=0; i<c.length(); i++){
        (*c.at(i)).updateParentSize();
        (*c.at(i)).updateSizeReferences();
    }
}

void SGWWidget::updateParentSize(){
    if(parent == nullptr){
        (*this).parentW1 = 1.0f;
        (*this).parentW0 = 0.0f;
        (*this).parentH1 = 1.0f;
        (*this).parentH0 = 0.0f;
    }
    else{
        (*this).parentW1 = (*parent).w1 * (*parent).parentW1;
        (*this).parentW0 = (*parent).w1 * (*parent).parentW0 + (*parent).w0;
        (*this).parentH1 = (*parent).h1 * (*parent).parentH1;
        (*this).parentH0 = (*parent).h1 * (*parent).parentH0 + (*parent).h0;
    }
    (*(*this).topObject).setProperty("pw1", (*this).parentW1);
    (*(*this).topObject).setProperty("pw0", (*this).parentW0);
    (*(*this).topObject).setProperty("ph1", (*this).parentH1);
    (*(*this).topObject).setProperty("ph0", (*this).parentH0);
}
