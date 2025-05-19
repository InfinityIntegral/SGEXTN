#ifndef SGTEXT022221131_H
#define SGTEXT022221131_H

#include <QWidget>
#include <QLabel>

class SGText022221131 : public QLabel
{
    Q_OBJECT
public:
    SGText022221131(QWidget *parent, QString s, float x, float y);
    float x;
    float y;

public slots:
    void ResizeObj();
};

#endif // SGTEXT022221131_H
