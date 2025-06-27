#ifndef SGXQUICKRESIZER_H
#define SGXQUICKRESIZER_H

#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>
#include <qtmetamacros.h>

class SGXQuickResizer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float appWindowWidth READ getAppWindowWidth WRITE setAppWindowWidth NOTIFY changedAppWindowWidth FINAL);
    Q_PROPERTY(float appWindowHeight READ getAppWindowHeight WRITE setAppWindowHeight NOTIFY changedAppWindowHeight FINAL);
    Q_PROPERTY(float renderSpaceWidth READ getRenderSpaceWidth WRITE setRenderSpaceWidth NOTIFY changedRenderSpaceWidth FINAL);
    Q_PROPERTY(float renderSpaceHeight READ getRenderSpaceHeight WRITE setRenderSpaceHeight NOTIFY changedRenderSpaceHeight FINAL);
    Q_PROPERTY(float sizeUnit READ getSizeUnit WRITE setSizeUnit NOTIFY changedSizeUnit FINAL)
public:
    SGXQuickResizer();
    float appWindowWidth;
    [[nodiscard]] float getAppWindowWidth() const;
    void setAppWindowWidth(float x);
    float appWindowHeight;
    [[nodiscard]] float getAppWindowHeight() const;
    void setAppWindowHeight(float x);
    float renderSpaceWidth;
    [[nodiscard]] float getRenderSpaceWidth() const;
    void setRenderSpaceWidth(float x);
    float renderSpaceHeight;
    [[nodiscard]] float getRenderSpaceHeight() const;
    void setRenderSpaceHeight(float x);
    float sizeUnit;
    [[nodiscard]] float getSizeUnit() const;
    void setSizeUnit(float x);
signals:
    void changedAppWindowWidth();
    void changedAppWindowHeight();
    void changedRenderSpaceWidth();
    void changedRenderSpaceHeight();
    void changedSizeUnit();
public slots:
    void updateAppWindowSize();
};

#endif // SGXQUICKRESIZER_H
