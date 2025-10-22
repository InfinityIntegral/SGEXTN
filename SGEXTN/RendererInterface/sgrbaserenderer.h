#ifndef SGRBASERENDERER_H
#define SGRBASERENDERER_H

class SGRRenderingProgramme;
class SGRRendererNode;
class SGRCommandRequest;
class SGRBaseRenderer
{
public:
    SGRBaseRenderer();
    SGRBaseRenderer(const SGRBaseRenderer&) = delete;
    SGRBaseRenderer& operator=(const SGRBaseRenderer&) = delete;
    SGRBaseRenderer(SGRBaseRenderer&&) = delete;
    SGRBaseRenderer& operator=(SGRBaseRenderer&&) = delete;
    virtual void initialise() = 0;
    virtual SGRRenderingProgramme* createRenderingProgramme() = 0;
    virtual void uploadShaderData() = 0;
    virtual void requestRenderCommands(SGRCommandRequest* commandRequest) = 0;
    virtual void cleanResourcesOnDestruction() = 0;
    virtual ~SGRBaseRenderer() = default;
    SGRRenderingProgramme* renderingProgramme();
    SGRRendererNode* node;
    bool initialised;
    float internalX;
    float internalY;
    float internalW;
    float internalH;
    float internalWindowW;
    float internalWindowH;
};

#endif // SGRBASERENDERER_H
