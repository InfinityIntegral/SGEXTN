#ifndef SGXVESICLESMATERIAL_H
#define SGXVESICLESMATERIAL_H

#include <QSGMaterial>
#include "../primitives/sgxvector2.h"
#include <QVector2D>

class SGXVesiclesMaterial : public QSGMaterial
{
public:
    SGXVesiclesMaterial(float cx, float cy, float r, float x, float y, float w, float h, float s);
    float cx;
    float cy;
    float r;
    float x;
    float y;
    float w;
    float h;
    float s;
    QSGMaterialShader* createShader(QSGRendererInterface::RenderMode) const override;
    QSGMaterialType* type() const override;
    int compare(const QSGMaterial *other) const override;
};

#endif // SGXVESICLESMATERIAL_H
