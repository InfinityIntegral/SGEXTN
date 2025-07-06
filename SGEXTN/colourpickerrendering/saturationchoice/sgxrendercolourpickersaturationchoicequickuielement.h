#ifndef SGXRENDERCOLOURPICKERSATURATIONCHOICEQUICKUIELEMENT_H
#define SGXRENDERCOLOURPICKERSATURATIONCHOICEQUICKUIELEMENT_H

#include <qtmetamacros.h>
#include <QQuickItem>

class SGXRenderColourPickerSaturationChoiceQuickUIElement : public QQuickItem
{
    Q_OBJECT
public:
    SGXRenderColourPickerSaturationChoiceQuickUIElement();
    QSGNode* updatePaintNode(QSGNode *thisNode, UpdatePaintNodeData */*unused*/) override;
    float selectedHue;
    float selectedSaturation;
};

#endif // SGXRENDERCOLOURPICKERSATURATIONCHOICEQUICKUIELEMENT_H
