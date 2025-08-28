#ifndef SGWICONLABEL_H
#define SGWICONLABEL_H

#include "../noninstantiable/sgwlabel.h"
#include <QChar>

class SGWWidget;
class SGWIconLabel : public SGWLabel
{
public:
    SGWIconLabel(SGWWidget* parent, QChar s, float x1, float x0, float y1, float y0, float w1, float w0);
    [[nodiscard]] QChar getChar() const;
    void setChar(QChar c);
protected:
    QChar textChar;
};

#endif // SGWICONLABEL_H
