#include "sgxrendercutevesiclesquickuielement.h"
#include <QSGGeometryNode>
#include "sgxrendercutevesiclesmaterial.h"
#include <QRandomGenerator>
#include "../quickui/sgxquickuiinterface.h"
#include <QTimer>

namespace{
inline float randomFloat(float min, float max){
    double x = (*QRandomGenerator::global()).generateDouble();
    x = static_cast<double>(min) + x * (static_cast<double>(max) - static_cast<double>(min));
    return static_cast<float>(x);
}
}

float SGXRenderCuteVesiclesQuickUIElement::framesPerSecond = 10.0f;
bool SGXRenderCuteVesiclesQuickUIElement::animationOngoing = false;
SGXRenderCuteVesiclesQuickUIElement* SGXRenderCuteVesiclesQuickUIElement::animationScreen = nullptr;

void SGXRenderCuteVesiclesQuickUIElement::startAnimation(){
    SGXRenderCuteVesiclesQuickUIElement::animationOngoing = true;
    if(SGXRenderCuteVesiclesQuickUIElement::animationScreen == nullptr){SGXRenderCuteVesiclesQuickUIElement::animationScreen = static_cast<SGXRenderCuteVesiclesQuickUIElement*>(SGXQuickUIInterface::createCuteVesicles(SGXQuickUIInterface::rootWidget));}
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

QSGNode* SGXRenderCuteVesiclesQuickUIElement::updatePaintNode(QSGNode *thisNode, UpdatePaintNodeData *){
    QSGGeometryNode* n = static_cast<QSGGeometryNode*>(thisNode);
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
        unsigned short* tg = (*g).indexDataAsUShort();
        tg[0] = 0;
        tg[1] = 1;
        tg[2] = 2;
        tg[3] = 1;
        tg[4] = 2;
        tg[5] = 3;
    }
    QSGGeometry::Point2D* vt = (*(*n).geometry()).vertexDataAsPoint2D();
    SGXRenderCuteVesiclesMaterial* mat = static_cast<SGXRenderCuteVesiclesMaterial*>((*n).material());
    float x = (*this).x();
    float y = (*this).y();
    float w = (*this).width();
    float h = (*this).height();
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
        (*mat).velocity[i] += (SGXVector2(randomFloat((-1.0f) * (*mat).maxAccelerationPerSecond, (*mat).maxAccelerationPerSecond), randomFloat((-1.0f) * (*mat).maxAccelerationPerSecond, (*mat).maxAccelerationPerSecond)) / SGXRenderCuteVesiclesQuickUIElement::framesPerSecond);
        if((*mat).velocity[i].x > (*mat).maxVelocityAllowed){(*mat).velocity[i].x = (*mat).maxVelocityAllowed;}
        else if((*mat).velocity[i].x < (-1.0f) * (*mat).maxVelocityAllowed){(*mat).velocity[i].x = -1.0f * (*mat).maxVelocityAllowed;}
        if((*mat).velocity[i].y > (*mat).maxVelocityAllowed){(*mat).velocity[i].y = (*mat).maxVelocityAllowed;}
        else if((*mat).velocity[i].y < (-1.0f) * (*mat).maxVelocityAllowed){(*mat).velocity[i].y = -1.0f * (*mat).maxVelocityAllowed;}
        (*mat).center[i] += (*mat).velocity[i] / SGXRenderCuteVesiclesQuickUIElement::framesPerSecond;
        if((*mat).center[i].x > (*mat).maxCenter){(*mat).center[i].x -= 2.0f * (*mat).maxCenter;}
        else if((*mat).center[i].x < (-1.0f) * (*mat).maxCenter){(*mat).center[i].x += 2.0f * (*mat).maxCenter;}
        if((*mat).center[i].y > (*mat).maxCenter){(*mat).center[i].y -= 2.0f * (*mat).maxCenter;}
        else if((*mat).center[i].y < (-1.0f) * (*mat).maxCenter){(*mat).center[i].y += 2.0f * (*mat).maxCenter;}
        (*mat).radius[i] += randomFloat((-1.0f) * (*mat).maxRadiusChangePerSecond, (*mat).maxRadiusChangePerSecond) / SGXRenderCuteVesiclesQuickUIElement::framesPerSecond;
        if((*mat).radius[i] > (*mat).maxRadiusAllowed){(*mat).radius[i] = (*mat).maxRadiusAllowed;}
        else if((*mat).radius[i] < (*mat).minRadiusAllowed){(*mat).radius[i] = (*mat).minRadiusAllowed;}
        for(int j=0; j<8; j++){
            (*mat).radiusOffset[i][j] += randomFloat((-1.0f) * (*mat).maxRadiusOffsetChangePerSecond, (*mat).maxRadiusOffsetChangePerSecond) / SGXRenderCuteVesiclesQuickUIElement::framesPerSecond;
            if((*mat).radiusOffset[i][j] > (*mat).maxRadiusOffsetAsRadiusPercentage){(*mat).radiusOffset[i][j] = (*mat).maxRadiusOffsetAsRadiusPercentage;}
            else if((*mat).radiusOffset[i][j] < (-1.0f) * (*mat).maxRadiusOffsetAsRadiusPercentage){(*mat).radiusOffset[i][j] = (-1.0f) * (*mat).maxRadiusOffsetAsRadiusPercentage;}
        }
    }
    (*n).markDirty(QSGNode::DirtyMaterial | QSGNode::DirtyGeometry);
    return n;
}
