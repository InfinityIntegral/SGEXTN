#ifndef SGXVESICLEPROPERTIESPAGE_H
#define SGXVESICLEPROPERTIESPAGE_H

#include <QQuickItem>
#include <QObject>
#include <qtmetamacros.h>

class SGXVesiclePropertiesPage : public QObject
{
    Q_OBJECT
public:
    SGXVesiclePropertiesPage() = delete;
    static QQuickItem* instance;
    static void initialise();
    static QQuickItem* membraneColourInput;
    static QQuickItem* contentsColourInput;
    static QQuickItem* membraneThicknessInput;
    static QQuickItem* maximumCenterDistanceInput;
    static QQuickItem* maximumVelocityInput;
    static QQuickItem* maximumAccelerationInput;
    static QQuickItem* maximumRadiusChangeInput;
    static QQuickItem* maximumRadiusInput;
    static QQuickItem* minimumRadiusInput;
    static QQuickItem* maximumRadiusOffsetInput;
    static QQuickItem* maximumRadiusOffsetChangeInput;
    static QQuickItem* membraneTransparencyInput;
    static QQuickItem* centerTransparencyInput;
    static QQuickItem* edgeTransparencyInput;
    static QQuickItem* frameRateInput;
signals:
    void doNothing();
public slots:
    static void activate();
};

#endif // SGXVESICLEPROPERTIESPAGE_H
