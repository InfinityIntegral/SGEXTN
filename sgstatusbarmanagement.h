#ifndef SGSTATUSBARMANAGEMENT_H
#define SGSTATUSBARMANAGEMENT_H

#include <QObject>
#include "sgwidget000411102.h"
#include "sgtext022221131.h"

class SGStatusBarManagement : public QObject
{
    Q_OBJECT
public:
    static SGWidget000411102* statusbarbackground;
    static void initialisestatusbar();
    static QTimer* timecounter;
    static SGText022221131* timedisplay;
    static void updatetime();
    static bool isnotifying;
    static void notify(QString s);
    static void donenotify();
private:
    SGStatusBarManagement(){}
    ~SGStatusBarManagement(){}
};

#endif // SGSTATUSBARMANAGEMENT_H
