#ifndef SGRTESTRENDERER_H
#define SGRTESTRENDERER_H

#include "../sgrbaserenderer.h"

class SGRCommandRequest;
class SGRVertexBufferObject;
class SGRElementBufferObject;
class SGRTestRenderer : public SGRBaseRenderer
{
public:
    SGRTestRenderer();
    void initialise() override;
    SGRRenderingProgramme* createRenderingProgramme() override;
    void uploadShaderData() override;
    void requestRenderCommands(SGRCommandRequest* commandRequest) override;
    void cleanResourcesOnDestruction() override;
    ~SGRTestRenderer() override;
    SGRVertexBufferObject* vbo;
    SGRElementBufferObject* ebo;
};

#endif // SGRTESTRENDERER_H
