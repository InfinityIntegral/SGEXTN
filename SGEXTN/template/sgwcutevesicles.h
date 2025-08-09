#ifndef SGWCUTEVESICLES_H
#define SGWCUTEVESICLES_H

#include <QObject>
#include "../cutevesicles/sgxrendercutevesiclessgwidget.h"
#include <QTimer>
#include <qtmetamacros.h>

class SGWCuteVesicles : public QObject
{
    Q_OBJECT
public:
    SGWCuteVesicles() = delete;
    static float framesPerSecond;
    static SGXRenderCuteVesiclesSGWidget* instance;
    static QTimer* timer;
    static void startAnimation();
    static void stopAnimation();
    static void toggleAnimation();
signals:
    void nothingChanged();
public slots:
    static void refreshAnimation();
};

#endif // SGWCUTEVESICLES_H
