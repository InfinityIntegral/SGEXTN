#ifndef SGXRENDERCUTEVESICLESQUICKUIELEMENT_H
#define SGXRENDERCUTEVESICLESQUICKUIELEMENT_H

#include <QQuickItem>
#include <qtmetamacros.h>

class SGXRenderCuteVesiclesQuickUIElement : public QQuickItem
{
    Q_OBJECT
public:
    SGXRenderCuteVesiclesQuickUIElement(); // create instance of animation
    QSGNode* updatePaintNode(QSGNode* thisNode, UpdatePaintNodeData* /*unused*/) override; // function to update animation screen
};

#endif // SGXRENDERCUTEVESICLESQUICKUIELEMENT_H
