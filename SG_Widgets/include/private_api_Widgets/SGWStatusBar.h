#ifndef SGWSTATUSBAR_H
#define SGWSTATUSBAR_H

#include <SGWWidget.h>

#include <private_api_Widgets/SG_Build_Widgets.h>

class SGXTimer;
class SGXString;
class SG_WIDGETS_DLL SGWStatusBar : public SGWWidget
{
public:
    SGWStatusBar();
    static SGWStatusBar* instance;
    static SGXTimer* timer;
    static void terminate();
    static void updateTime();
};

#endif // SGWSTATUSBAR_H
