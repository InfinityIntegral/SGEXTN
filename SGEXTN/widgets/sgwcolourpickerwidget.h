#ifndef SGWCOLOURPICKERWIDGET_H
#define SGWCOLOURPICKERWIDGET_H

#include <qtmetamacros.h>
#include "../widgets/sgwwidget.h"
#include "../primitives/sgxcolourrgba.h"
#include <QString>

class SGWColourPickerWidget : public SGWWidget
{
    Q_OBJECT
public:
    SGWColourPickerWidget(SGWWidget* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, SGXColourRGBA defaultColour);
    void syncQuickProperties();
    [[nodiscard]] SGXColourRGBA getColour() const;
    void setColour(SGXColourRGBA colour);
protected:
    SGXColourRGBA colour = {};
public slots:
    void eventReceived(const QString& s);
};

#endif // SGWCOLOURPICKERWIDGET_H
