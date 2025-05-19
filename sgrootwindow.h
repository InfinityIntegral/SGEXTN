#ifndef SGROOTWINDOW_H
#define SGROOTWINDOW_H

#include <QWidget>
#include <QTimer>

class SGRootWindow : public QWidget
{
    Q_OBJECT
public:
    SGRootWindow();
    void updatescreensize();
    QTimer* t;
};

#endif // SGROOTWINDOW_H
