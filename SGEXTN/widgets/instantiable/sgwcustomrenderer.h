#ifndef SGWCUSTOMRENDERER_H
#define SGWCUSTOMRENDERER_H

#include "../noninstantiable/sgwwidget.h"

class SGXString;
template <typename T1, typename T2> class QHash;
class QQmlComponent;
class SGWCustomRenderer : public SGWWidget
{
public:
    SGWCustomRenderer(SGWWidget* parent, const SGXString& qmlCodeLocation, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
    static QHash<SGXString, QQmlComponent*>* componentDatabase;
    void redraw();
};

#endif // SGWCUSTOMRENDERER_H
