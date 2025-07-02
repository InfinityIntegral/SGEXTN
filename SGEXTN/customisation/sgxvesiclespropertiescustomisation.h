#ifndef SGXVESICLESPROPERTIESCUSTOMISATION_H
#define SGXVESICLESPROPERTIESCUSTOMISATION_H

#include <QObject>
#include <qtmetamacros.h>

class SGXVesiclesPropertiesCustomisation : public QObject
{
    Q_OBJECT
public:
    SGXVesiclesPropertiesCustomisation() = delete;
    static void loadVesicleProperties(); // load vesicle properties from file
    // note that during the National Day period, the vesicles will use the same colour as the red on our flag for their membranes and the same shade of white for their contents, because vesicles need to wear red and white to celebrate also
    static void syncVesicleProperties(); // write current vesicle properties to file
};

#endif // SGXVESICLESPROPERTIESCUSTOMISATION_H
