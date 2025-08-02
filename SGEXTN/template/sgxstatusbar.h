#ifndef SGXSTATUSBAR_H
#define SGXSTATUSBAR_H

#include <QObject>
#include <QQuickItem>
#include <QTimer>
#include <qtmetamacros.h>

class SGXStatusBar : public QObject // non instantiable class to manage status bar
{
    Q_OBJECT
public:
    SGXStatusBar() = delete;
    static QQuickItem* instance; // instance of status bar
    static QTimer* timer; // instance of recurring timer to manage status bar
    static int secondsLeft; // number of seconds left in notification
    static void notify(const QString& notificationMessage, int timeInSeconds); // function to send a notification into the status bar
    static bool isNotifying;
signals:
    void nothingChanged();
public slots:
    static void updateTime(); // function to update time display
};

#endif // SGXSTATUSBAR_H
