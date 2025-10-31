#ifndef SGWWIDGETQUICKINTERFACE_H
#define SGWWIDGETQUICKINTERFACE_H

#include <QObject>

class SGXString;
class SGWWidget;
class SGWWidgetQuickInterface : public QObject
{
public:
    SGWWidgetQuickInterface(SGWWidget* x);
    SGWWidget* x;
    void eventReceivedWithQString(const QString& event) const;
    void eventReceived(const SGXString& event) const;
};

#endif // SGWWIDGETQUICKINTERFACE_H
