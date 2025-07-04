#ifndef SGXSTATUSBAR_H
#define SGXSTATUSBAR_H

#include <QObject>
#include <QQuickItem>
#include <QTimer>
#include <qtmetamacros.h>

class SGXStatusBar : public QObject
{
    Q_OBJECT
public:
    SGXStatusBar() = delete;
    static QQuickItem* instance;
    static QTimer* timer;
signals:
    void nothingChanged();
public slots:
    static void updateTime();
};

#endif // SGXSTATUSBAR_H
