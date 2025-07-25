#ifndef SGXRENDERCOLOURBACKGROUNDQUICKUIELEMENT_H
#define SGXRENDERCOLOURBACKGROUNDQUICKUIELEMENT_H

#include <qtmetamacros.h>
#include <QQuickItem>

class SGXRenderColourBackgroundQuickUIElement : public QQuickItem
{
    Q_OBJECT
public:
    SGXRenderColourBackgroundQuickUIElement();
    QSGNode* updatePaintNode(QSGNode *thisNode, UpdatePaintNodeData */*unused*/) override;
};

#endif // SGXRENDERCOLOURBACKGROUNDQUICKUIELEMENT_H
