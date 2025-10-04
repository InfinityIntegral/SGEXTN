#ifndef SGWNOTIFY_H
#define SGWNOTIFY_H

template <typename T> class SGLQueue;
class SGWWidget;
class SGWLabel;
class SGXTimer;
class SGXString;
class SGWNotify
{
public:
    SGWNotify() = delete;
    static float timeShown;
    static SGLQueue<SGWWidget*>* instance;
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
