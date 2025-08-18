#ifndef SGWSTATUSBAR_H
#define SGWSTATUSBAR_H

#include <QObject>
#include <QTimer>
#include <qtmetamacros.h>
#include "../noninstantiable/sgwwidget.h"

class SGWStatusBar : public SGWWidget
{
    Q_OBJECT
public:
    SGWStatusBar();
    static int notificationTime;
    static SGWStatusBar* instance;
    static QTimer* timer;
    static int timeLeft;
    static bool isNotifying;
    static void terminate();
    static void notify(const QString& s);
    static void toggleVesicles();
signals:
    void nothingChanged();
public slots:
    static void updateTime();
    static void eventReceived(const QString& s);
};

#endif // SGWSTATUSBAR_H
