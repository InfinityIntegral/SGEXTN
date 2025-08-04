#ifndef SGWICONBUTTON_H
#define SGWICONBUTTON_H

#include <qtmetamacros.h>
#include "sgwbutton.h"
#include "sgwwidget.h"
#include <QChar>

class SGWIconButton : public SGWButton
{
    Q_OBJECT
public:
    SGWIconButton(SGWWidget* parent, QChar s, void (*attachedFunction)(SGWButton*), float x1, float x0, float y1, float y0, float w1, float w0);
    [[nodiscard]] QChar getChar() const;
    void setChar(QChar c);
protected:
    QChar textChar;
};

#endif // SGWICONBUTTON_H
