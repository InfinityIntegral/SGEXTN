#ifndef SGXCUTEVESICLES_H
#define SGXCUTEVESICLES_H

#include <QObject>
#include "../cutevesicles/sgxrendercutevesiclesquickuielement.h"
#include <QTimer>
#include <qtmetamacros.h>

class SGXCuteVesicles : public QObject // non instantiable class to manage vesicle animations
{
    Q_OBJECT
public:
    SGXCuteVesicles() = delete;
    static float framesPerSecond; // frame count of animation
    static bool animationOngoing; // checks if animation is active
    static SGXRenderCuteVesiclesQuickUIElement* animationScreen; // reference to animation widget
    static QTimer* timer; // recurring timer to refresh frame
signals:
    void nothingChanged();
public slots:
    static void refreshAnimation(); // call for refresh to animation screen
    static void startAnimation(); // start animation and create or show widget
    static void stopAnimation(); // stop animation and hide widget
    static void toggleAnimation(); // toggle animation state
};

#endif // SGXCUTEVESICLES_H
