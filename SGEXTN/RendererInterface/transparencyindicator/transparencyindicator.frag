#version 310 es
precision highp float;
layout(std140, binding = 0) uniform SG_RI_builtin{
    vec4 SG_RI_this;
    vec4 SG_RI_window;
};
layout(location = 0) in vec2 vertexUnits;
layout(location = 0) out vec4 outColour;

void main(){
    int i = (int(vertexUnits.x) + int(vertexUnits.y)) % 2;
    float f = 0.15f * float(i);
    outColour = vec4(0.8f + f, 0.8f + f, 0.8f + f, 1.0f);
}
