#ifndef SGXVESICLESPROPERTIESCUSTOMISATION_H
#define SGXVESICLESPROPERTIESCUSTOMISATION_H

class SGXVesiclesPropertiesCustomisation
{
public:
    SGXVesiclesPropertiesCustomisation() = delete;
    static void loadVesicleProperties();
    static void syncVesicleProperties();
};

#endif // SGXVESICLESPROPERTIESCUSTOMISATION_H
