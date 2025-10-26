#ifndef SGRCOLOURPICKERRENDERER_H
#define SGRCOLOURPICKERRENDERER_H

#include "../sgrbaserenderer.h"

class SGRVertexBufferObject;
class SGRElementBufferObject;
class SGRColourPickerRenderer : public SGRBaseRenderer
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
