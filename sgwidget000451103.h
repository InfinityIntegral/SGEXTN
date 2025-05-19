#ifndef SGWIDGET000451103_H
#define SGWIDGET000451103_H

#include <QWidget>

class SGWidget000451103 : public QWidget
{
    Q_OBJECT
public:
    SGWidget000451103(QWidget *parent, float x, float y, float h1, float h0);
    float x;
    float y;
    float h1;
    float h0;

public slots:
    void ResizeObj();
};

#endif // SGWIDGET000451103_H
