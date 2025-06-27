#ifndef SGXRENDERCUTEVESICLESQUICKUIELEMENT_H
#define SGXRENDERCUTEVESICLESQUICKUIELEMENT_H

#include <QQuickItem>

class SGXRenderCuteVesiclesQuickUIElement : public QQuickItem
{
    Q_OBJECT
public:
    SGXRenderCuteVesiclesQuickUIElement();
    QSGNode* updatePaintNode(QSGNode* thisNode, UpdatePaintNodeData*) override;
    static float framesPerSecond;
    static bool animationOngoing;
    static SGXRenderCuteVesiclesQuickUIElement* animationScreen;
public slots:
    static void refreshAnimation();
    static void startAnimation();
    static void stopAnimation();
};

#endif // SGXRENDERCUTEVESICLESQUICKUIELEMENT_H
