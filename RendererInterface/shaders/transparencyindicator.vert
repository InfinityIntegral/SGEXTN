#version 310 es
precision highp float;
precision highp int;
layout(std140, binding = 0) uniform SG_RI_builtin_{
    float x;
    float y;
    float width;
    float height;
    float windowWidth;
    float windowHeight;
    int offscreen;
} SG_RI_builtin;
vec4 SG_RI_transform(vec4 prelimPosition){
    prelimPosition = vec4(2.0f * (prelimPosition.x * SG_RI_builtin.width / SG_RI_builtin.windowWidth + SG_RI_builtin.x / SG_RI_builtin.windowWidth) - 1.0f, -2.0f * (prelimPosition.y * SG_RI_builtin.height / SG_RI_builtin.windowHeight + SG_RI_builtin.y / SG_RI_builtin.windowHeight) + 1.0f, prelimPosition.z, prelimPosition.w);
    if(SG_RI_builtin.offscreen != 0){prelimPosition = vec4(prelimPosition.x, -1.0f * prelimPosition.y, prelimPosition.z, prelimPosition.w);}
    return prelimPosition;
}
layout(location = 0) in vec2 vertex;
layout(location = 0) out vec2 vertexUnits;

void main(){
    gl_Position = vec4(vertex.x, vertex.y, 0.0f, 1.0f);
    vertexUnits = vec2(5.0f * vertex.x * SG_RI_builtin.width / SG_RI_builtin.height, 5.0f * vertex.y);
    
    gl_Position = SG_RI_transform(gl_Position);
}
