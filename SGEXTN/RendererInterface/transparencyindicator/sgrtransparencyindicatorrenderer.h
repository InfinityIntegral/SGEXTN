#ifndef SGRTRANSPARENCYINDICATORRENDERER_H
#define SGRTRANSPARENCYINDICATORRENDERER_H

#include "../sgrbaserenderer.h"

class SGRVertexBufferObject;
class SGRElementBufferObject;
class SGRTransparencyIndicatorRenderer : public SGRBaseRenderer
{
public:
    SGRTransparencyIndicatorRenderer();
    SGRRenderingProgramme* createRenderingProgramme() override;
    void initialise() override;
    void cleanResourcesOnDestruction() override;
    void uploadShaderData() override;
    void requestRenderCommands(SGRCommandRequest* commandRequest) override;
    SGRVertexBufferObject* vbo;
    SGRElementBufferObject* ebo;
};

#endif // SGRTRANSPARENCYINDICATORRENDERER_H
