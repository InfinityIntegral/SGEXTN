#ifndef SGWSTATUSBAR_H
#define SGWSTATUSBAR_H

#include <QObject>
#include "../../timer/sgxtimer.h"
#include <qtmetamacros.h>
#include "../noninstantiable/sgwwidget.h"

class SGWStatusBar : public SGWWidget
{
    Q_OBJECT
public:
    SGWStatusBar();
    static int notificationTime;
    static SGWStatusBar* instance;
    static SGXTimer* timer;
    static int timeLeft;
    static bool isNotifying;
    static void terminate();
    static void notify(const QString& s);
    static void toggleVesicles();
    static void updateTime();
signals:
    void nothingChanged();
public slots:
    static void eventReceived(const QString& s);
};

#endif // SGWSTATUSBAR_H
