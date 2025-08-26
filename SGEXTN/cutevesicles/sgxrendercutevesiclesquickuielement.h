#ifndef SGXRENDERCUTEVESICLESQUICKUIELEMENT_H
#define SGXRENDERCUTEVESICLESQUICKUIELEMENT_H

#include <QQuickItem>
#include <qtmetamacros.h>

class SGXRenderCuteVesiclesQuickUIElement : public QQuickItem
{
    Q_OBJECT
public:
    SGXRenderCuteVesiclesQuickUIElement();
    QSGNode* updatePaintNode(QSGNode* thisNode, UpdatePaintNodeData* /*unused*/) override;
};

#endif // SGXRENDERCUTEVESICLESQUICKUIELEMENT_H
