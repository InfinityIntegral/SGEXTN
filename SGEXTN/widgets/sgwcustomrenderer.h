#ifndef SGWCUSTOMRENDERER_H
#define SGWCUSTOMRENDERER_H

#include <qtmetamacros.h>
#include "sgwwidget.h"
#include <QString>
#include <QHash>
#include <QQmlComponent>

class SGWCustomRenderer : public SGWWidget
{
    Q_OBJECT
public:
    SGWCustomRenderer(SGWWidget* parent, const QString& qmlCodeLocation, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
    static QHash<QString, QQmlComponent*>* componentDatabase;
};

#endif // SGWCUSTOMRENDERER_H
