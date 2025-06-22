#ifndef SGXQUICKRESIZER_H
#define SGXQUICKRESIZER_H

#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>

class SGXQuickResizer : public QObject
{
    Q_OBJECT // NOLINT
    Q_PROPERTY(float appWindowWidth READ getAppWindowWidth WRITE setAppWindowWidth NOTIFY changedAppWindowWidth FINAL); // NOLINT
    Q_PROPERTY(float appWindowHeight READ getAppWindowHeight WRITE setAppWindowHeight NOTIFY changedAppWindowHeight FINAL); // NOLINT
public:
    SGXQuickResizer();
    static QObject* getObject(QQmlEngine* me, QJSEngine* se);
    float appWindowWidth;
    [[nodiscard]] float getAppWindowWidth() const;
    void setAppWindowWidth(float x);
    float appWindowHeight;
    [[nodiscard]] float getAppWindowHeight() const;
    void setAppWindowHeight(float x);
signals: // NOLINT
    void changedAppWindowWidth();
    void changedAppWindowHeight();
public slots: // NOLINT
    void updateAppWindowSize();
};

#endif // SGXQUICKRESIZER_H
