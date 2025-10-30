#ifndef SGRTRANSPARENCYINDICATORRENDERER_H
#define SGRTRANSPARENCYINDICATORRENDERER_H

#include <SGRBaseRenderer.h>

#include <private_api_RI/SG_Build_RI.h>

class SGRVertexBufferObject;
class SGRElementBufferObject;
class SG_RI_DLL SGRTransparencyIndicatorRenderer : public SGRBaseRenderer
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
