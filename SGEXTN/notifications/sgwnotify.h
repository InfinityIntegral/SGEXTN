#ifndef SGWNOTIFY_H
#define SGWNOTIFY_H

#include "../widgets/noninstantiable/sgwwidget.h"
#include "../widgets/noninstantiable/sgwlabel.h"
#include <queue>
#include "../timer/sgxtimer.h"

class SGWNotify
{
public:
    SGWNotify() = delete;
    static float timeShown;
    static std::queue<SGWWidget*>* instance;
    static void notify(const QString& s);
    static void terminate();
    static int animationStage;
    static bool animationState;
    static float animationLength;
    static void animate();
    static void pullDownNotify(const QString& s);
    static SGWLabel* pullDownInstance;
    static SGXTimer* pullDownTimer;
};

#endif // SGWNOTIFY_H
