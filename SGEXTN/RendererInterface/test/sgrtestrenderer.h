#ifndef SGRTESTRENDERER_H
#define SGRTESTRENDERER_H

#include "../sgrbaserenderer.h"
#include "../../primitives/sgxcolourrgba.h"

class SGRCommandRequest;
class SGRVertexBufferObject;
class SGRElementBufferObject;
class SGRImage;
class SGRTestRenderer : public SGRBaseRenderer
{
public:
    SGRTestRenderer();
    void initialise() override;
    SGRRenderingProgramme* createRenderingProgramme() override;
    void uploadShaderData() override;
    void requestRenderCommands(SGRCommandRequest* commandRequest) override;
    void cleanResourcesOnDestruction() override;
    SGRVertexBufferObject* vboPosition;
    SGRVertexBufferObject* vboColour;
    SGRElementBufferObject* ebo;
    SGRImage* img;
};

#endif // SGRTESTRENDERER_H
