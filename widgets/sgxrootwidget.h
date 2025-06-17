#ifndef SGXROOTWIDGET_H
#define SGXROOTWIDGET_H

#include <QWidget>
#include <QTimer>

class SGXRootWidget : public QWidget // root widget of application with resize timer
{
    Q_OBJECT // NOLINT
public:
    SGXRootWidget(); // create root widget
    QTimer* t; // timer used to check if the window has been resized
    void paintEvent(QPaintEvent*) override; // NOLINT(readability-named-parameter)
public slots: // NOLINT
    void checkScreenSizeUpdate(); // function to check if the window has been resized, run 60 times per second
};

#endif // SGXROOTWIDGET_H
