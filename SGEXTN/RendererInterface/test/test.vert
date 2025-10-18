#version 310 es
precision highp float;
layout(location = 0) in vec2 vertex;
layout(std140, binding = 0) uniform SG_RI_builtin{
    vec4 SG_RI_this;
    vec4 SG_RI_window;
};
vec4 SG_RI_transform(vec4 prelimPosition){
    return vec4(2.0f * (prelimPosition.x * SG_RI_this.z / SG_RI_window.x + SG_RI_this.x / SG_RI_window.x) - 1.0f, -2.0f * (prelimPosition.y * SG_RI_this.w / SG_RI_window.y + SG_RI_this.y / SG_RI_window.y) + 1.0f, prelimPosition.z, prelimPosition.w);
}

void main(){
    gl_Position = vec4(vertex.x, vertex.y, 0.0f, 1.0f);
    
    gl_Position = SG_RI_transform(gl_Position);
}
