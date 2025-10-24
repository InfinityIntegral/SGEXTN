#version 310 es
precision highp float;
layout(std140, binding = 0) uniform SG_RI_builtin{
    vec4 SG_RI_this;
    vec4 SG_RI_window;
};
layout(binding = 1) uniform sampler2D tx;
layout(location = 0) in vec2 imgCoords;
layout(location = 0) out vec4 outColour;

void main(){
    outColour = texture(tx, imgCoords);
    //outColour = vec4(imgCoords.x, imgCoords.y, 0.0f, 1.0f);
}
