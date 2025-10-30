#ifndef SGWWIDGETQUICKINTERFACE_H
#define SGWWIDGETQUICKINTERFACE_H

#include <QObject>

#include <private_api_Widgets/SG_Build_Widgets.h>

class SGXString;
class SGWWidget;
class SG_WIDGETS_DLL SGWWidgetQuickInterface : public QObject
{
public:
    SGWWidgetQuickInterface(SGWWidget* x);
    SGWWidget* x;
    void eventReceivedWithQString(const QString& event) const;
    void eventReceived(const SGXString& event) const;
};

#endif // SGWWIDGETQUICKINTERFACE_H
