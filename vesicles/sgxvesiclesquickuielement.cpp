#include "sgxvesiclesquickuielement.h"
#include <QSGGeometryNode>
#include <QSGGeometry>
#include "sgxvesiclesmaterial.h"

SGXVesiclesQuickUIElement::SGXVesiclesQuickUIElement(){
    (*this).setFlag(QQuickItem::ItemHasContents, true);
    (*this).setProperty("layer.enabled", true);
}

QSGNode* SGXVesiclesQuickUIElement::updatePaintNode(QSGNode *thisNode, UpdatePaintNodeData *){
    QSGGeometryNode* n = static_cast<QSGGeometryNode*>(thisNode);
    if(n == nullptr){
        n = new QSGGeometryNode();
        QSGGeometry* g = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 4, 6);
        (*g).setDrawingMode(QSGGeometry::DrawTriangles);
        (*n).setGeometry(g);
        (*n).setFlag(QSGNode::OwnsGeometry);
        SGXVesiclesMaterial* m = new SGXVesiclesMaterial(0.5f, 0.5f, 0.25f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
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
    SGXVesiclesMaterial* mat = static_cast<SGXVesiclesMaterial*>((*n).material());
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
    return n;
}
