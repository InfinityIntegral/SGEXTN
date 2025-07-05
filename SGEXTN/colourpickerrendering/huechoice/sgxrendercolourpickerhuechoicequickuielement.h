#ifndef SGXRENDERCOLOURPICKERHUECHOICEQUICKUIELEMENT_H
#define SGXRENDERCOLOURPICKERHUECHOICEQUICKUIELEMENT_H

#include <qtmetamacros.h>
#include <QQuickItem>

class SGXRenderColourPickerHueChoiceQuickUIElement : public QQuickItem
{
    Q_OBJECT
public:
    SGXRenderColourPickerHueChoiceQuickUIElement();
    QSGNode* updatePaintNode(QSGNode* thisNode, UpdatePaintNodeData* /*unused*/) override;
    float selectedHue;
};

#endif // SGXRENDERCOLOURPICKERHUECHOICEQUICKUIELEMENT_H
