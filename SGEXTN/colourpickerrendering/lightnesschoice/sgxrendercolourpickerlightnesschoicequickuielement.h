#ifndef SGXRENDERCOLOURPICKERLIGHTNESSCHOICEQUICKUIELEMENT_H
#define SGXRENDERCOLOURPICKERLIGHTNESSCHOICEQUICKUIELEMENT_H

#include <QQuickItem>

class SGXRenderColourPickerLightnessChoiceQuickUIElement : public QQuickItem
{
public:
    SGXRenderColourPickerLightnessChoiceQuickUIElement();
    QSGNode* updatePaintNode(QSGNode *thisNode, UpdatePaintNodeData */*unused*/) override;
    float selectedHue;
    float selectedSaturation;
    float selectedLightness;
};

#endif // SGXRENDERCOLOURPICKERLIGHTNESSCHOICEQUICKUIELEMENT_H
