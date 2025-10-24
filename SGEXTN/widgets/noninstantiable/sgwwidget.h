#ifndef SGWWIDGET_H
#define SGWWIDGET_H

#include "../enums/sgwtype.h"
#include "../../containers/sglarray.h"

class QQuickItem;
class SGRImage;
class SGWWidget
{
public:
    SGWWidget() = delete;
    SGWWidget(const SGWWidget&) = delete;
    SGWWidget& operator=(const SGWWidget&) = delete;
    SGWWidget(SGWWidget&&) = delete;
    SGWWidget& operator=(SGWWidget&&) = delete;
    virtual ~SGWWidget();
    [[nodiscard]] SGWType::Type getType() const;
    [[nodiscard]] SGWWidget* getParent() const;
    [[nodiscard]] SGLArray<SGWWidget*> getChildren() const;
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
    void updateParentSizeNoPush();
    void updateParentSize();
    void syncQuickProperties();
    void initialiseQuickItemReferences(QQuickItem* thisItem);
    static SGWWidget* rootWidget;
    static SGWWidget* parentWidget;
    [[nodiscard]] bool getItemVisibility() const;
    void setItemVisibility(bool x);
    void screenshot(void (*callback)(SGRImage*));
public:
    SGWWidget(SGWWidget* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
    SGWType::Type type;
    SGWWidget* parent;
    SGLArray<SGWWidget*> children = SGLArray<SGWWidget*>(0);
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
