#ifndef SGXRENDERCOLOURPICKERSATURATIONCHOICEQUICKUIELEMENT_H
#define SGXRENDERCOLOURPICKERSATURATIONCHOICEQUICKUIELEMENT_H

#include <QQuickItem>

class SGXRenderColourPickerSaturationChoiceQuickUIElement : public QQuickItem
{
public:
    SGXRenderColourPickerSaturationChoiceQuickUIElement();
    QSGNode* updatePaintNode(QSGNode *thisNode, UpdatePaintNodeData */*unused*/) override;
    float selectedHue;
    float selectedSaturation;
};

#endif // SGXRENDERCOLOURPICKERSATURATIONCHOICEQUICKUIELEMENT_H
