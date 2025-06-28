#ifndef SGXRENDERCUTEVESICLESQUICKUIELEMENT_H
#define SGXRENDERCUTEVESICLESQUICKUIELEMENT_H

#include <QQuickItem>
#include <qtmetamacros.h>

class SGXRenderCuteVesiclesQuickUIElement : public QQuickItem
{
    Q_OBJECT
public:
    SGXRenderCuteVesiclesQuickUIElement(); // create instance of animation
    QSGNode* updatePaintNode(QSGNode* thisNode, UpdatePaintNodeData* /*unused*/) override; // function to update animation screen
    static float framesPerSecond; // frame count of animation
    static bool animationOngoing; // checks if animation is active
    static SGXRenderCuteVesiclesQuickUIElement* animationScreen; // reference to animation widget
signals:
    void nothingChanged();
public slots:
    static void refreshAnimation(); // call for refresh to animation screen
    static void startAnimation(); // start animation and create or show widget
    static void stopAnimation(); // stop animation and hide widget
};

#endif // SGXRENDERCUTEVESICLESQUICKUIELEMENT_H
