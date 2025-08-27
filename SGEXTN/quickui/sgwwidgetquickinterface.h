#ifndef SGWWIDGETQUICKINTERFACE_H
#define SGWWIDGETQUICKINTERFACE_H

#include <QObject>
#include "../widgets/noninstantiable/sgwwidget.h"
#include <qtmetamacros.h>

class SGWWidgetQuickInterface : public QObject
{
    Q_OBJECT
public:
    SGWWidgetQuickInterface(SGWWidget* x);
    SGWWidget* x;
signals:
    void doNothing();
public slots:
    void eventReceived(const QString& event);
};

#endif // SGWWIDGETQUICKINTERFACE_H
