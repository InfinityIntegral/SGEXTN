#include "sgxvesiclesquickuielement.h"
#include <QSGGeometryNode>
#include <QSGGeometry>
#include "sgxvesiclesmaterial.h"
#include <QDebug>

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
        SGXVesiclesMaterial* m = new SGXVesiclesMaterial(SGXVector2(100.0f, 100.0f), 20.0f);
        (*n).setMaterial(m);
        (*n).setFlag(QSGNode::OwnsMaterial);
        (*g).allocate(4, 6);
        QSGGeometry::Point2D* vt = (*g).vertexDataAsPoint2D();
        unsigned short* tg = (*g).indexDataAsUShort();
        float w = (*this).width();
        float h = (*this).height();
        
        vt[0].set(0, 0);
        vt[1].set(w, 0);
        vt[2].set(0, h);
        vt[3].set(w, h);
        
        tg[0] = 0;
        tg[1] = 1;
        tg[2] = 2;
        tg[3] = 1;
        tg[4] = 2;
        tg[5] = 3;
    }
    qDebug() << n;
    return n;
}
