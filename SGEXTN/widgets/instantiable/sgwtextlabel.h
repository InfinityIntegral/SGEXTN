#ifndef SGWTEXTLABEL_H
#define SGWTEXTLABEL_H

#include <qtmetamacros.h>
#include "../noninstantiable/sgwlabel.h"
#include "../noninstantiable/sgwwidget.h"
#include <QString>
#include "../enums/sgwhorizontalalignment.h"

class SGWTextLabel : public SGWLabel
{
    Q_OBJECT
public:
    SGWTextLabel(SGWWidget* parent, const QString& s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, SGWHorizontalAlignment::Flag alignment, bool isWarning);
};

#endif // SGWTEXTLABEL_H
