#include "sgxrendercutevesiclesquickuielement.h"
#include <QSGGeometryNode>
#include "sgxrendercutevesiclesmaterial.h"
#include <QRandomGenerator>
#include "../quickui/sgxquickuiinterface.h"
#include <QTimer>
#include <QQuickItem>
#include <QSGGeometry>
#include <algorithm>
#include "../primitives/sgxvector2.h"
#include <QObject>
#include <span>

namespace{
inline float randomFloat(float min, float max){
    double x = (*QRandomGenerator::global()).generateDouble();
    x = static_cast<double>(min) + x * (static_cast<double>(max) - static_cast<double>(min));
    return static_cast<float>(x);
}
}

float SGXRenderCuteVesiclesQuickUIElement::framesPerSecond = 0.0f;
bool SGXRenderCuteVesiclesQuickUIElement::animationOngoing = false;
SGXRenderCuteVesiclesQuickUIElement* SGXRenderCuteVesiclesQuickUIElement::animationScreen = nullptr;

void SGXRenderCuteVesiclesQuickUIElement::startAnimation(){
    SGXRenderCuteVesiclesQuickUIElement::animationOngoing = true;
    if(SGXRenderCuteVesiclesQuickUIElement::animationScreen == nullptr){SGXRenderCuteVesiclesQuickUIElement::animationScreen = qobject_cast<SGXRenderCuteVesiclesQuickUIElement*>(SGXQuickUIInterface::createCuteVesicles(SGXQuickUIInterface::rootWidget));}
    (*SGXRenderCuteVesiclesQuickUIElement::animationScreen).setVisible(true);
    SGXRenderCuteVesiclesQuickUIElement::refreshAnimation();
}

void SGXRenderCuteVesiclesQuickUIElement::refreshAnimation(){
    if(SGXRenderCuteVesiclesQuickUIElement::animationOngoing == true){
        (*SGXRenderCuteVesiclesQuickUIElement::animationScreen).update();
        QTimer::singleShot(static_cast<int>(1000.0f / SGXRenderCuteVesiclesQuickUIElement::framesPerSecond), &SGXRenderCuteVesiclesQuickUIElement::refreshAnimation);
    }
}

void SGXRenderCuteVesiclesQuickUIElement::stopAnimation(){
    SGXRenderCuteVesiclesQuickUIElement::animationOngoing = false;
    (*SGXRenderCuteVesiclesQuickUIElement::animationScreen).setVisible(false);
}

SGXRenderCuteVesiclesQuickUIElement::SGXRenderCuteVesiclesQuickUIElement(){
    (*this).setFlag(QQuickItem::ItemHasContents, true);
}

QSGNode* SGXRenderCuteVesiclesQuickUIElement::updatePaintNode(QSGNode *thisNode, UpdatePaintNodeData */*unused*/){
    QSGGeometryNode* n = dynamic_cast<QSGGeometryNode*>(thisNode);
    if(n == nullptr){
        n = new QSGGeometryNode();
        QSGGeometry* g = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 4, 6);
        (*g).setDrawingMode(QSGGeometry::DrawTriangles);
        (*n).setGeometry(g);
        (*n).setFlag(QSGNode::OwnsGeometry);
        SGXRenderCuteVesiclesMaterial* m = new SGXRenderCuteVesiclesMaterial();
        (*n).setMaterial(m);
        (*n).setFlag(QSGNode::OwnsMaterial);
        (*g).allocate(4, 6);
        unsigned short* tgPointer = (*g).indexDataAsUShort();
        const std::span<unsigned short> tg(tgPointer, 6);
        tg[0] = 0;
        tg[1] = 1;
        tg[2] = 2;
        tg[3] = 1;
        tg[4] = 2;
        tg[5] = 3;
    }
    QSGGeometry::Point2D* vtPointer = (*(*n).geometry()).vertexDataAsPoint2D();
    const std::span<QSGGeometry::Point2D> vt(vtPointer, 4);
    SGXRenderCuteVesiclesMaterial* mat = dynamic_cast<SGXRenderCuteVesiclesMaterial*>((*n).material());
    const float x = static_cast<float>((*this).x());
    const float y = static_cast<float>((*this).y());
    const float w = static_cast<float>((*this).width());
    const float h = static_cast<float>((*this).height());
    vt[0].set(0, 0);
    vt[1].set(w, 0);
    vt[2].set(0, h);
    vt[3].set(w, h);
    (*mat).x = x;
    (*mat).y = y;
    (*mat).w = w;
    (*mat).h = h;
    (*mat).s = std::max(w, h);
    for(int i=0; i<10; i++){
        (*mat).velocity.at(i) += (SGXVector2(randomFloat((-1.0f) * (*mat).maxAccelerationPerSecond, (*mat).maxAccelerationPerSecond), randomFloat((-1.0f) * (*mat).maxAccelerationPerSecond, (*mat).maxAccelerationPerSecond)) / SGXRenderCuteVesiclesQuickUIElement::framesPerSecond);
        if((*mat).velocity.at(i).x > (*mat).maxVelocityAllowed){(*mat).velocity.at(i).x = (*mat).maxVelocityAllowed;}
        else if((*mat).velocity.at(i).x < (-1.0f) * (*mat).maxVelocityAllowed){(*mat).velocity.at(i).x = -1.0f * (*mat).maxVelocityAllowed;}
        if((*mat).velocity.at(i).y > (*mat).maxVelocityAllowed){(*mat).velocity.at(i).y = (*mat).maxVelocityAllowed;}
        else if((*mat).velocity.at(i).y < (-1.0f) * (*mat).maxVelocityAllowed){(*mat).velocity.at(i).y = -1.0f * (*mat).maxVelocityAllowed;}
        (*mat).center.at(i) += (*mat).velocity.at(i) / SGXRenderCuteVesiclesQuickUIElement::framesPerSecond;
        if((*mat).center.at(i).x > (*mat).maxCenter){(*mat).center.at(i).x -= 2.0f * (*mat).maxCenter;}
        else if((*mat).center.at(i).x < (-1.0f) * (*mat).maxCenter){(*mat).center.at(i).x += 2.0f * (*mat).maxCenter;}
        if((*mat).center.at(i).y > (*mat).maxCenter){(*mat).center.at(i).y -= 2.0f * (*mat).maxCenter;}
        else if((*mat).center.at(i).y < (-1.0f) * (*mat).maxCenter){(*mat).center.at(i).y += 2.0f * (*mat).maxCenter;}
        (*mat).radius.at(i) += randomFloat((-1.0f) * (*mat).maxRadiusChangePerSecond, (*mat).maxRadiusChangePerSecond) / SGXRenderCuteVesiclesQuickUIElement::framesPerSecond;
        if((*mat).radius.at(i) > (*mat).maxRadiusAllowed){(*mat).radius.at(i) = (*mat).maxRadiusAllowed;}
        else if((*mat).radius.at(i) < (*mat).minRadiusAllowed){(*mat).radius.at(i) = (*mat).minRadiusAllowed;}
        for(int j=0; j<8; j++){
            (*mat).radiusOffset.at(i).at(j) += randomFloat((-1.0f) * (*mat).maxRadiusOffsetChangePerSecond, (*mat).maxRadiusOffsetChangePerSecond) / SGXRenderCuteVesiclesQuickUIElement::framesPerSecond;
            if((*mat).radiusOffset.at(i).at(j) > (*mat).maxRadiusOffsetAsRadiusPercentage){(*mat).radiusOffset.at(i).at(j) = (*mat).maxRadiusOffsetAsRadiusPercentage;}
            else if((*mat).radiusOffset.at(i).at(j) < (-1.0f) * (*mat).maxRadiusOffsetAsRadiusPercentage){(*mat).radiusOffset.at(i).at(j) = (-1.0f) * (*mat).maxRadiusOffsetAsRadiusPercentage;}
        }
    }
    (*n).markDirty(QSGNode::DirtyMaterial | QSGNode::DirtyGeometry);
    return n;
}
