#ifndef SGWWIDGETQUICKINTERFACE_H
#define SGWWIDGETQUICKINTERFACE_H

#include <QObject>
#include "../widgets/noninstantiable/sgwwidget.h"

class SGWWidgetQuickInterface : public QObject
{
public:
    SGWWidgetQuickInterface(SGWWidget* x);
    SGWWidget* x;
    void eventReceived(const QString& event);
};

#endif // SGWWIDGETQUICKINTERFACE_H
