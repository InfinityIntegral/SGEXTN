#ifndef SGWWIDGETQUICKINTERFACE_H
#define SGWWIDGETQUICKINTERFACE_H

#include <QObject>

class SGWWidget;
class SGWWidgetQuickInterface : public QObject
{
public:
    SGWWidgetQuickInterface(SGWWidget* x);
    SGWWidget* x;
    void eventReceived(const QString& event) const;
};

#endif // SGWWIDGETQUICKINTERFACE_H
