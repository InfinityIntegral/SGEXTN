#ifndef SGXROOTWIDGET_H
#define SGXROOTWIDGET_H

#include <QWidget>
#include <QTimer>

class SGXRootWidget : public QWidget // root widget of application with resize timer
{
    Q_OBJECT // NOLINT
public:
    SGXRootWidget();
    QTimer* t;
public slots: // NOLINT
    void checkScreenSizeUpdate();
};

#endif // SGXROOTWIDGET_H
