#version 310 es
precision highp float;
layout(std140, binding = 0) uniform SG_RI_builtin{
    vec4 SG_RI_this;
    vec4 SG_RI_window;
};
layout(location = 0) out vec4 outColour;

void main(){
    outColour = vec4(0.0f, 0.0f, 0.0f, 0.5f);
}
