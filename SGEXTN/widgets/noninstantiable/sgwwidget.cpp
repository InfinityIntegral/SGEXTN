#include "sgwwidget.h"
#include "../enums/sgwtype.h"
#include <QQuickItem>
#include "../instantiable/sgwscrollview.h"
#include "../../quickui/sgxquickinterface.h"
#include "../instantiable/sgwsequentialscrollview.h"
#include "../../containers/sglarray.h"
#include "../../quickui/sgrscreenshotcallback.h"

SGWWidget* SGWWidget::rootWidget = nullptr;
SGWWidget* SGWWidget::parentWidget = nullptr;

SGWWidget::SGWWidget(SGWWidget* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0){
    (*this).type = SGWType::Undefined;
    (*this).children = SGLArray<SGWWidget*>(0);
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
    (*this).parentW1 = 0.0f;
    (*this).parentW0 = 0.0f;
    (*this).parentH1 = 0.0f;
    (*this).parentH0 = 0.0f;
    (*this).parent = parent;
    if((*this).parent != nullptr){
        SGLArray<SGWWidget*> newChildren((*(*this).parent).children.length() + 1);
        for(int i=0; i<(*(*this).parent).children.length(); i++){
            newChildren.at(i) = (*(*this).parent).children.at(i);
        }
        newChildren.at((*(*this).parent).children.length()) = this;
        (*(*this).parent).children = newChildren;
    }
    updateParentSizeNoPush();
}

SGWWidget::~SGWWidget(){
    for(int i=0; i<children.length(); i++){delete children.at(i);}
    (*topObject).deleteLater();
    if(parent != nullptr){
        SGLArray<SGWWidget*> newChildren((*(*this).parent).children.length() - 1);
        int j = 0;
        for(int i=0; i<(*(*this).parent).children.length(); i++){
            if((*(*this).parent).children.at(i) == this){continue;}
            newChildren.at(j) = (*(*this).parent).children.at(i);
            j++;
        }
        (*(*this).parent).children = newChildren;
    }
}

void SGWWidget::initialiseQuickItemReferences(QQuickItem *thisItem){
    (*thisItem).setParentItem((*parent).getBottomObject());
    (*thisItem).setParent((*parent).getBottomObject());
    (*this).topObject = thisItem;
    (*this).bottomObject = SGXQuickInterface::getBottomObject(thisItem);
}

SGWType::Type SGWWidget::getType() const {
    return type;
}

SGWWidget* SGWWidget::getParent() const {
    return parent;
}

SGLArray<SGWWidget*> SGWWidget::getChildren() const {
    return children;
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
    const SGLArray<SGWWidget*> c = getChildren();
    for(int i=0; i<c.length(); i++){
        (*c.at(i)).updateParentSize(); // NOLINT(clang-analyzer-core.CallAndMessage)
        (*c.at(i)).updateSizeReferences();
    }
}

void SGWWidget::updateParentSizeNoPush(){
    if(parent == nullptr){
        (*this).parentW1 = 1.0f;
        (*this).parentW0 = 0.0f;
        (*this).parentH1 = 1.0f;
        (*this).parentH0 = 0.0f;
    }
    else{
        if((*parent).type == SGWType::ScrollView){
            SGWScrollView* parentScrollView = static_cast<SGWScrollView*>(parent);
            const float scrollViewW1 = (*parentScrollView).w1 - (*parentScrollView).getS1();
            const float scrollViewW0 = (*parentScrollView).w0 - (*parentScrollView).getS0();
            const float scrollViewH1 = (*parentScrollView).getI1();
            const float scrollViewH0 = (*parentScrollView).getI0();
            (*this).parentW1 = scrollViewW1 * (*parent).parentW1;
            (*this).parentW0 = scrollViewW1 * (*parent).parentW0 + scrollViewW0;
            (*this).parentH1 = scrollViewH1 * (*parent).parentH1;
            (*this).parentH0 = scrollViewH1 * (*parent).parentH0 + scrollViewH0;
        }
        else if((*parent).type == SGWType::SequentialScrollView){
            SGWSequentialScrollView* parentScrollView = static_cast<SGWSequentialScrollView*>(parent);
            const float scrollViewW1 = (*parentScrollView).w1 - (*parentScrollView).getS1();
            const float scrollViewW0 = (*parentScrollView).w0 - (*parentScrollView).getS0();
            (*this).parentW1 = scrollViewW1 * (*parent).parentW1;
            (*this).parentW0 = scrollViewW1 * (*parent).parentW0 + scrollViewW0;
            (*this).parentH1 = (*parent).h1 * (*parent).parentH1;
            (*this).parentH0 = (*parent).h1 * (*parent).parentH0 + (*parent).h0;
        }
        else{
            (*this).parentW1 = (*parent).w1 * (*parent).parentW1;
            (*this).parentW0 = (*parent).w1 * (*parent).parentW0 + (*parent).w0;
            (*this).parentH1 = (*parent).h1 * (*parent).parentH1;
            (*this).parentH0 = (*parent).h1 * (*parent).parentH0 + (*parent).h0;
        }
    }
}

void SGWWidget::updateParentSize(){
    updateParentSizeNoPush();
    (*(*this).topObject).setProperty("pw1", (*this).parentW1);
    (*(*this).topObject).setProperty("pw0", (*this).parentW0);
    (*(*this).topObject).setProperty("ph1", (*this).parentH1);
    (*(*this).topObject).setProperty("ph0", (*this).parentH0);
}

void SGWWidget::syncQuickProperties(){
    (*topObject).setProperty("x1", x1);
    (*topObject).setProperty("x0", x0);
    (*topObject).setProperty("y1", y1);
    (*topObject).setProperty("y0", y0);
    (*topObject).setProperty("w1", w1);
    (*topObject).setProperty("w0", w0);
    (*topObject).setProperty("h1", h1);
    (*topObject).setProperty("h0", h0);
    (*topObject).setProperty("pw1", parentW1);
    (*topObject).setProperty("pw0", parentW0);
    (*topObject).setProperty("ph1", parentH1);
    (*topObject).setProperty("ph0", parentH0);
}

bool SGWWidget::getItemVisibility() const {
    return (*topObject).isVisible();
}

void SGWWidget::setItemVisibility(bool x){
    if((*topObject).isVisible() == x){return;}
    (*topObject).setVisible(x);
}

void SGWWidget::screenshot(void (*callback)(SGRImage *)){
    new SGRScreenshotCallback(callback, getTopObject());
}
