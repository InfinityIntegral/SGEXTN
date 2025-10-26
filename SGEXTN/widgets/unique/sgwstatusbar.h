#ifndef SGWSTATUSBAR_H
#define SGWSTATUSBAR_H

#include "../noninstantiable/sgwwidget.h"

class SGWWidgetQuickInterface;
class SGXTimer;
class SGXString;
class SGWStatusBar : public SGWWidget
{
public:
    SGWStatusBar();
    static SGWStatusBar* instance;
    static SGXTimer* timer;
    static void terminate();
    static void updateTime();
};

#endif // SGWSTATUSBAR_H
