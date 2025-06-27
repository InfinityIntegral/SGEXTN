#ifndef SGXRENDERCUTEVESICLESQUICKUIELEMENT_H
#define SGXRENDERCUTEVESICLESQUICKUIELEMENT_H

#include <QQuickItem>
#include <qtmetamacros.h>

class SGXRenderCuteVesiclesQuickUIElement : public QQuickItem
{
    Q_OBJECT
public:
    SGXRenderCuteVesiclesQuickUIElement();
    QSGNode* updatePaintNode(QSGNode* thisNode, UpdatePaintNodeData* /*unused*/) override;
    static float framesPerSecond;
    static bool animationOngoing;
    static SGXRenderCuteVesiclesQuickUIElement* animationScreen;
signals:
    void nothingChanged();
public slots:
    static void refreshAnimation();
    static void startAnimation();
    static void stopAnimation();
};

#endif // SGXRENDERCUTEVESICLESQUICKUIELEMENT_H
