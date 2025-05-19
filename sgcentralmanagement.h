#ifndef SGCENTRALMANAGEMENT_H
#define SGCENTRALMANAGEMENT_H

#include <QObject>
#include "sgrootwindow.h"
#include "sgsignalsemitter.h"
#include "sgwidget000451103.h"

class SGCentralManagement : public QObject
{
    Q_OBJECT
public:
    static QString colour0;
    static QString colour1;
    static QString colour2;
    static QString colour3;
    static float screenw;
    static float screenh;
    static float renderw;
    static float renderh;
    static float sizeunit;
    static SGRootWindow* rootwindow;
    static SGSignalsEmitter* signalsemitter;
    static SGWidget000451103* mainbackground;
    static void initialise();
    static void terminate();
private:
    SGCentralManagement(){}
    ~SGCentralManagement(){}
};

#endif // SGCENTRALMANAGEMENT_H
