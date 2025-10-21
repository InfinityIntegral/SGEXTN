#ifndef SGRBASERENDERER_H
#define SGRBASERENDERER_H

class SGRRenderingProgramme;
class SGRRendererNode;
class SGRCommandRequest;
class SGRBaseRenderer
{
public:
    SGRBaseRenderer() = default;
    virtual SGRRenderingProgramme* createRenderingProgramme() = 0;
    virtual void uploadShaderData() = 0;
    virtual void requestRenderCommands(SGRCommandRequest* commandRequest) = 0;
    virtual void cleanResourcesOnDestruction() = 0;
    virtual ~SGRBaseRenderer() = default;
    SGRRenderingProgramme* renderingProgramme();
    SGRRendererNode* node;
};

#endif // SGRBASERENDERER_H
