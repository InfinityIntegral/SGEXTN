#ifndef SGXRENDERCOLOURPICKERLIGHTNESSCHOICEQUICKUIELEMENT_H
#define SGXRENDERCOLOURPICKERLIGHTNESSCHOICEQUICKUIELEMENT_H

#include <qtmetamacros.h>
#include <QQuickItem>

class SGXRenderColourPickerLightnessChoiceQuickUIElement : public QQuickItem
{
    Q_OBJECT
public:
    SGXRenderColourPickerLightnessChoiceQuickUIElement();
    QSGNode* updatePaintNode(QSGNode *thisNode, UpdatePaintNodeData */*unused*/) override;
    float selectedHue;
    float selectedSaturation;
    float selectedLightness;
};

#endif // SGXRENDERCOLOURPICKERLIGHTNESSCHOICEQUICKUIELEMENT_H
