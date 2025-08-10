#ifndef SGWSEQUENTIALLONGLABEL_H
#define SGWSEQUENTIALLONGLABEL_H

#include <qtmetamacros.h>
#include "sgwlabel.h"
#include "sgwwidget.h"
#include <QString>

class SGWSequentialLongLabel : public SGWLabel
{
    Q_OBJECT
public:
    SGWSequentialLongLabel(SGWWidget* parent, const QString& s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
};

#endif // SGWSEQUENTIALLONGLABEL_H
