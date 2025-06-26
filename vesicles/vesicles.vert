#version 310 es
precision highp float;
layout(location = 0) in vec2 vertex;
layout(std140, binding = 0) uniform uvq{
	uniform mat4 qt_Matrix;
	uniform float frag_qt_Opacity;
	uniform vec2 frag_c;
	uniform float frag_r;
};
layout(location = 0) out float qt_Opacity;
layout(location = 1) out vec2 c;
layout(location = 2) out float r;

void main(){
	gl_Position = vec4(vertex.x / 726.0, vertex.y / 695.75, 0.0, 1.0);
}
