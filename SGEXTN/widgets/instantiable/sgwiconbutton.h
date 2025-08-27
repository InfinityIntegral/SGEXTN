#ifndef SGWICONBUTTON_H
#define SGWICONBUTTON_H

#include "../noninstantiable/sgwbutton.h"
#include "../noninstantiable/sgwwidget.h"
#include <QChar>

class SGWIconButton : public SGWButton
{
public:
    SGWIconButton(SGWWidget* parent, QChar s, void (*attachedFunction)(SGWButton*), float x1, float x0, float y1, float y0, float w1, float w0);
    [[nodiscard]] QChar getChar() const;
    void setChar(QChar c);
protected:
    QChar textChar;
};

#endif // SGWICONBUTTON_H
