#ifndef SGXRENDERCUTEVESICLESQUICKUIELEMENT_H
#define SGXRENDERCUTEVESICLESQUICKUIELEMENT_H

#include <QQuickItem>

class SGXRenderCuteVesiclesQuickUIElement : public QQuickItem
{
public:
    SGXRenderCuteVesiclesQuickUIElement();
    QSGNode* updatePaintNode(QSGNode* thisNode, UpdatePaintNodeData* /*unused*/) override;
};

#endif // SGXRENDERCUTEVESICLESQUICKUIELEMENT_H
