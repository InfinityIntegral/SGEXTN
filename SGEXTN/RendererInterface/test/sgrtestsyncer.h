#ifndef SGRTESTSYNCER_H
#define SGRTESTSYNCER_H

#include "../sgrbasesyncer.h"
#include "../../primitives/sgxcolourrgba.h"

class SGRTestSyncer : public SGRBaseSyncer
{
public:
    SGRTestSyncer();
    void sync(SGRBaseRenderer* renderControl) override;
};

#endif // SGRTESTSYNCER_H
