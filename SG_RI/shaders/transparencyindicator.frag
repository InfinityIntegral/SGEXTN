#version 310 es
precision highp float;
layout(location = 0) in vec2 vertexUnits;
layout(location = 0) out vec4 outColour;

void main(){
    float f = 0.15f * mod(floor(vertexUnits.x) + floor(vertexUnits.y), 2.0f);
    outColour = vec4(0.8f + f, 0.8f + f, 0.8f + f, 1.0f);
}
