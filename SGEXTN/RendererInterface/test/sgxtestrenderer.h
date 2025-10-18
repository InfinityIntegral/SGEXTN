#ifndef SGXTESTRENDERER_H
#define SGXTESTRENDERER_H

#include "../sgrbaserenderer.h"

class SGXTestRenderer : public SGRBaseRenderer
{
public:
    SGXTestRenderer();
    static SGRBaseRenderer* getInstance();
    void prepareRenderCommands() override;
    void runRenderCommands() override;
    void cleanResourcesOnDestruction() override;
    ~SGXTestRenderer() = default;
};

#endif // SGXTESTRENDERER_H
