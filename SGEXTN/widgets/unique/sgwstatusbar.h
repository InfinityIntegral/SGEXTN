#ifndef SGWSTATUSBAR_H
#define SGWSTATUSBAR_H

#include "../../timer/sgxtimer.h"
#include "../noninstantiable/sgwwidget.h"

class SGWWidgetQuickInterface;
class SGWStatusBar : public SGWWidget
{
public:
    SGWStatusBar();
    ~SGWStatusBar() override;
    static SGWStatusBar* instance;
    static SGXTimer* timer;
    static void terminate();
    static void toggleVesicles();
    static void updateTime();
    static void eventReceived(const QString& s);
protected:
    SGWWidgetQuickInterface* quickInterface;
};

#endif // SGWSTATUSBAR_H
