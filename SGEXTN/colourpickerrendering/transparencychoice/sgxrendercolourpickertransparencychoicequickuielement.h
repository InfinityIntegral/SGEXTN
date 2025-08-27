#ifndef SGXRENDERCOLOURPICKERTRANSPARENCYCHOICEQUICKUIELEMENT_H
#define SGXRENDERCOLOURPICKERTRANSPARENCYCHOICEQUICKUIELEMENT_H

#include <QQuickItem>

class SGXRenderColourPickerTransparencyChoiceQuickUIElement : public QQuickItem
{
public:
    SGXRenderColourPickerTransparencyChoiceQuickUIElement();
    QSGNode* updatePaintNode(QSGNode *thisNode, UpdatePaintNodeData */*unused*/) override;
    float selectedHue;
    float selectedSaturation;
    float selectedLightness;
    float selectedTransparency;
};

#endif // SGXRENDERCOLOURPICKERTRANSPARENCYCHOICEQUICKUIELEMENT_H
