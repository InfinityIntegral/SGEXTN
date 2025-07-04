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
signals:
    void nothingChanged();
public slots:
    static void updateTime(); // function to update time display
};

#endif // SGXSTATUSBAR_H
