#ifndef SGRRENDERERGENERATOR_H
#define SGRRENDERERGENERATOR_H

#include <QQuickItem>

#include <private_api_RI/SG_Build_RI.h>

class QSGNode;
class UpdatePaintNodeData;
class SGRBaseRenderer;
class SGWWidget;
class SGRBaseSyncer;
class SGRRendererNode;
class SG_RI_DLL SGRRendererGenerator : public QQuickItem
{
public:
    SGRRendererGenerator(SGRBaseRenderer* renderControl, SGRBaseSyncer* syncControl, SGWWidget* attachedWidget);
    SGRRendererGenerator(SGRBaseRenderer* renderControl, SGRBaseSyncer* syncControl, QQuickItem* parentItem);
    QSGNode* updatePaintNode(QSGNode* old, UpdatePaintNodeData* /*unused*/) override;
    SGRBaseRenderer* renderControl;
    SGRBaseSyncer* syncControl;
    SGWWidget* attachedWidget;
    void updatePolish() override;
    void syncSize();
    SGRRendererNode* node;
};

#endif // SGRRENDERERGENERATOR_H
