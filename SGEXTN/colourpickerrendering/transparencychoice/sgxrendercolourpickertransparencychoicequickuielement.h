#ifndef SGXRENDERCOLOURPICKERTRANSPARENCYCHOICEQUICKUIELEMENT_H
#define SGXRENDERCOLOURPICKERTRANSPARENCYCHOICEQUICKUIELEMENT_H

#include <qtmetamacros.h>
#include <QQuickItem>

class SGXRenderColourPickerTransparencyChoiceQuickUIElement : public QQuickItem
{
    Q_OBJECT
public:
    SGXRenderColourPickerTransparencyChoiceQuickUIElement();
    QSGNode* updatePaintNode(QSGNode *thisNode, UpdatePaintNodeData */*unused*/) override;
    float selectedHue;
    float selectedSaturation;
    float selectedLightness;
    float selectedTransparency;
};

#endif // SGXRENDERCOLOURPICKERTRANSPARENCYCHOICEQUICKUIELEMENT_H
