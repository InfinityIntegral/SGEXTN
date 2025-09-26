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
    SGWStatusBar(const SGWStatusBar&) = delete;
    SGWStatusBar& operator=(const SGWStatusBar&) = delete;
    SGWStatusBar(SGWStatusBar&&) = delete;
    SGWStatusBar& operator=(SGWStatusBar&&) = delete;
    ~SGWStatusBar() override;
    static SGWStatusBar* instance;
    static SGXTimer* timer;
    static void terminate();
    static void toggleVesicles();
    static void updateTime();
    static void eventReceived(const SGXString& s);
protected:
    SGWWidgetQuickInterface* quickInterface;
};

#endif // SGWSTATUSBAR_H
