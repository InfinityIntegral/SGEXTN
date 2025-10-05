#ifndef SGWCUSTOMRENDERER_H
#define SGWCUSTOMRENDERER_H

#include "../noninstantiable/sgwwidget.h"

class SGXString;
template <typename K, typename V, typename EqualityCheck, typename HashFunction> class SGLUnorderedMap;
template <typename T> class SGLEqualsTo;
template <typename T> class SGLHash;
class QQmlComponent;
class SGWCustomRenderer : public SGWWidget
{
public:
    SGWCustomRenderer(SGWWidget* parent, const SGXString& qmlCodeLocation, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
    static SGLUnorderedMap<SGXString, QQmlComponent*, SGLEqualsTo<SGXString>, SGLHash<SGXString>>* componentDatabase;
    void redraw();
};

#endif // SGWCUSTOMRENDERER_H
