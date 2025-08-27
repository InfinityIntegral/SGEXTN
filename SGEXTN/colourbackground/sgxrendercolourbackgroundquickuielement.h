#ifndef SGXRENDERCOLOURBACKGROUNDQUICKUIELEMENT_H
#define SGXRENDERCOLOURBACKGROUNDQUICKUIELEMENT_H

#include <QQuickItem>

class SGXRenderColourBackgroundQuickUIElement : public QQuickItem
{
public:
    SGXRenderColourBackgroundQuickUIElement();
    QSGNode* updatePaintNode(QSGNode *thisNode, UpdatePaintNodeData */*unused*/) override;
};

#endif // SGXRENDERCOLOURBACKGROUNDQUICKUIELEMENT_H
