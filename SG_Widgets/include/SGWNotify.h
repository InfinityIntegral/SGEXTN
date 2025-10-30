#ifndef SGWNOTIFY_H
#define SGWNOTIFY_H

#include <private_api_Widgets/SG_Build_Widgets.h>

template <typename T> class SGLQueue;
class SGWWidget;
class SGWLabel;
class SGXTimer;
class SGXString;
class SG_WIDGETS_DLL SGWNotify
{
public:
    SGWNotify() = delete;
    static float timeShown;
    static SGLQueue<const SGWWidget*>* instance;
    static void notify(const SGXString& s);
    static void terminate();
    static int animationStage;
    static bool animationState;
    static float animationLength;
    static void animate();
    static void pullDownNotify(const SGXString& s);
    static SGWLabel* pullDownInstance;
    static SGXTimer* pullDownTimer;
};

#endif // SGWNOTIFY_H
