#ifndef SGRCOLOURPICKERRENDERER_H
#define SGRCOLOURPICKERRENDERER_H

#include <SGRBaseRenderer.h>

#include <private_api_RI/SG_Build_RI.h>

class SGRVertexBufferObject;
class SGRElementBufferObject;
class SG_RI_DLL SGRColourPickerRenderer : public SGRBaseRenderer
{
public:
    SGRColourPickerRenderer(int type);
    int type;
    float hue;
    float saturation;
    float lightness;
    float transparency;
    SGRRenderingProgramme* createRenderingProgramme() override;
    void initialise() override;
    void cleanResourcesOnDestruction() override;
    void uploadShaderData() override;
    void requestRenderCommands(SGRCommandRequest* commandRequest) override;
    SGRVertexBufferObject* vbo;
    SGRElementBufferObject* ebo;
};

#endif // SGRCOLOURPICKERRENDERER_H
