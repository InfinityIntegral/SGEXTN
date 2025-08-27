#ifndef SGXRENDERCOLOURPICKERHUECHOICEQUICKUIELEMENT_H
#define SGXRENDERCOLOURPICKERHUECHOICEQUICKUIELEMENT_H

#include <QQuickItem>

class SGXRenderColourPickerHueChoiceQuickUIElement : public QQuickItem
{
public:
    SGXRenderColourPickerHueChoiceQuickUIElement();
    QSGNode* updatePaintNode(QSGNode* thisNode, UpdatePaintNodeData* /*unused*/) override;
    float selectedHue;
};

#endif // SGXRENDERCOLOURPICKERHUECHOICEQUICKUIELEMENT_H
