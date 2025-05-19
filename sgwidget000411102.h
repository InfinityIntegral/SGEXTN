#ifndef SGWIDGET000411102_H
#define SGWIDGET000411102_H

#include <QWidget>

class SGWidget000411102 : public QWidget
{
    Q_OBJECT
public:
    SGWidget000411102(QWidget *parent, float x, float y, float h);
    float x;
    float y;
    float h;

public slots:
    void ResizeObj();
};

#endif // SGWIDGET000411102_H
