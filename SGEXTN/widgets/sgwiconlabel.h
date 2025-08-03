#ifndef SGWICONLABEL_H
#define SGWICONLABEL_H

#include <qtmetamacros.h>
#include "sgwlabel.h"
#include <QChar>
#include "sgwwidget.h"

class SGWIconLabel : public SGWLabel
{
    Q_OBJECT
public:
    SGWIconLabel(SGWWidget* parent, const QChar& s, float x1, float x0, float y1, float y0, float w1, float w0);
    [[nodiscard]] QChar getChar() const;
    void setChar(QChar c);
protected:
    QChar textChar;
};

#endif // SGWICONLABEL_H
