#ifndef SGRRENDERERGENERATOR_H
#define SGRRENDERERGENERATOR_H

#include <QQuickItem>

class QSGNode;
class UpdatePaintNodeData;
class SGRBaseRenderer;
class SGWWidget;
class SGRBaseSyncer;
class SGRRendererGenerator : public QQuickItem
{
public:
    SGRRendererGenerator(SGRBaseRenderer* renderControl, SGRBaseSyncer* syncControl, SGWWidget* attachedWidget);
    QSGNode* updatePaintNode(QSGNode* old, UpdatePaintNodeData* /*unused*/) override;
    SGRBaseRenderer* renderControl;
    SGRBaseSyncer* syncControl;
    SGWWidget* attachedWidget;
    void updatePolish() override;
};

#endif // SGRRENDERERGENERATOR_H
