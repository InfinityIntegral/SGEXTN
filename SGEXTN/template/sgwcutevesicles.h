#ifndef SGWCUTEVESICLES_H
#define SGWCUTEVESICLES_H

class SGXTimer;
class SGXRenderCuteVesiclesSGWidget;
class SGWCuteVesicles
{
public:
    SGWCuteVesicles() = delete;
    static float framesPerSecond;
    static SGXRenderCuteVesiclesSGWidget* instance;
    static SGXTimer* timer;
    static void startAnimation();
    static void stopAnimation();
    static void toggleAnimation();
    static void refreshAnimation();
};

#endif // SGWCUTEVESICLES_H
