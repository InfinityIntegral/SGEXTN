#ifndef SGXVESICLESQUICKUIELEMENT_H
#define SGXVESICLESQUICKUIELEMENT_H

#include <QQuickItem>

class SGXVesiclesQuickUIElement : public QQuickItem
{
    Q_OBJECT
public:
    SGXVesiclesQuickUIElement();
    QSGNode* updatePaintNode(QSGNode* thisNode, UpdatePaintNodeData*) override;
};

#endif // SGXVESICLESQUICKUIELEMENT_H
