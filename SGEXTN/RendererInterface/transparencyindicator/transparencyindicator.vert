#version 310 es
precision highp float;
layout(std140, binding = 0) uniform SG_RI_builtin{
    vec4 SG_RI_this;
    vec4 SG_RI_window;
};
vec4 SG_RI_transform(vec4 prelimPosition){
    prelimPosition = vec4(2.0f * (prelimPosition.x * SG_RI_this.z / SG_RI_window.x + SG_RI_this.x / SG_RI_window.x) - 1.0f, -2.0f * (prelimPosition.y * SG_RI_this.w / SG_RI_window.y + SG_RI_this.y / SG_RI_window.y) + 1.0f, prelimPosition.z, prelimPosition.w);
    if(SG_RI_window.z != 0.0f){prelimPosition = vec4(prelimPosition.x, -1.0f * prelimPosition.y, prelimPosition.z, prelimPosition.a);}
    return prelimPosition;
}
layout(location = 0) in vec2 vertex;
layout(location = 0) out vec2 vertexUnits;

void main(){
    gl_Position = vec4(vertex.x, vertex.y, 0.0f, 1.0f);
    vertexUnits = vec2(5.0f * vertex.x * SG_RI_this.z / SG_RI_this.w, 5.0f * vertex.y);
    
    gl_Position = SG_RI_transform(gl_Position);
}
