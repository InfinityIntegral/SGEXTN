#ifndef SGWWIDGET_H
#define SGWWIDGET_H

#include <QObject>
#include <qtmetamacros.h>
#include "sgwtype.h"
#include "../primitives/sgxcolourrgba.h"
#include <QQuickItem>

class SGWWidget : public QObject
{
    Q_OBJECT
public:
    SGWWidget(SGWWidget* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, int themeColour, bool frequentlyUsed);
    ~SGWWidget();
    bool frequentlyUsed;
    SGWType::Type getType();
    int getThemeColour(bool* isValid);
    bool setThemeColour(int themeColour);
    SGXColourRGBA getColour(bool* isValid);
    bool setColour(SGXColourRGBA colour);
    SGWWidget* getParent();
    void setParent(SGWWidget* parent);
    QVector<SGWWidget*> getChildren();
    QQuickItem* getTopObject();
    QQuickItem* getBottomObject();
    float getX1();
    void setX1(float x1);
    float getX0();
    void setX0(float x0);
    float getY1();
    void setY1(float y1);
    float getY0();
    void setY0(float y0);
    float getW1();
    void setW1(float w1);
    float getW0();
    void setW0(float w0);
    float getH1();
    void setH1(float h1);
    float getH0();
    void setH0(float h0);
    bool getVisible();
    void enable(SGWWidget** pointerToThis, SGWWidget* (*initFunction)(), void (*resetFunction)());
    void disable(SGWWidget** pointerToThis);
private:
    SGWType::Type type;
    bool usingThemeColour;
    int themeColour;
    SGXColourRGBA colour;
    SGWWidget* parent;
    QVector<SGWWidget*> children;
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
    bool visible;
};

#endif // SGWWIDGET_H
