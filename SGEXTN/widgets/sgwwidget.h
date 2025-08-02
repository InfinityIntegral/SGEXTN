#ifndef SGWWIDGET_H
#define SGWWIDGET_H

#include <QObject>
#include <qtmetamacros.h>
#include "sgwtype.h"
#include <QQuickItem>
#include <QSet>
#include <qcontainerfwd.h>

class SGWWidget : public QObject
{
    Q_OBJECT
public:
    SGWWidget(SGWWidget* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
    SGWWidget(const SGWWidget&) = delete;
    SGWWidget& operator=(const SGWWidget&) = delete;
    SGWWidget(SGWWidget&&) = delete;
    SGWWidget& operator=(SGWWidget&&) = delete;
    ~SGWWidget() override;
    [[nodiscard]] SGWType::Type getType() const;
    [[nodiscard]] SGWWidget* getParent() const;
    [[nodiscard]] QVector<SGWWidget*> getChildren() const;
    [[nodiscard]] QQuickItem* getTopObject() const;
    [[nodiscard]] QQuickItem* getBottomObject() const;
    [[nodiscard]] float getX1() const;
    void setX1(float x1);
    [[nodiscard]] float getX0() const;
    void setX0(float x0);
    [[nodiscard]] float getY1() const;
    void setY1(float y1);
    [[nodiscard]] float getY0() const;
    void setY0(float y0);
    [[nodiscard]] float getW1() const;
    void setW1(float w1);
    [[nodiscard]] float getW0() const;
    void setW0(float w0);
    [[nodiscard]] float getH1() const;
    void setH1(float h1);
    [[nodiscard]] float getH0() const;
    void setH0(float h0);
    [[nodiscard]] float getParentW1() const;
    [[nodiscard]] float getParentW0() const;
    [[nodiscard]] float getParentH1() const;
    [[nodiscard]] float getParentH0() const;
    void updateSizeReferences();
    void updateParentSize();
    void syncQuickProperties();
    static SGWWidget* rootWidget;
    static SGWWidget* parentWidget;
protected:
    SGWType::Type type;
    SGWWidget* parent;
    QSet<SGWWidget*> children;
    QQuickItem* topObject;
    QQuickItem* bottomObject;
    float x1;
    float x0;
    float y1;
    float y0;
    float w1;
    float w0;
    float h1;
    float h0;
    float parentW1;
    float parentW0;
    float parentH1;
    float parentH0;
};

#endif // SGWWIDGET_H
