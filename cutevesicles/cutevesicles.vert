#version 310 es
precision highp float;
layout(location = 0) in vec2 vertex;
layout(std140, binding = 0) uniform uniformBuffer{
	uniform mat4 builtin_matrix;
	uniform float frag_builtin_opacity;
	uniform float frag_sizeX;
	uniform float frag_sizeY;
	uniform float frag_sizeW;
	uniform float frag_sizeH;
	uniform float frag_sizeS;
};
layout(location = 0) out float builtin_opacity;
layout(location = 1) out float sizeX;
layout(location = 2) out float sizeY;
layout(location = 3) out float sizeW;
layout(location = 4) out float sizeH;
layout(location = 5) out float sizeS;

void main(){
	sizeX = frag_sizeX;
	sizeY = frag_sizeY;
	sizeW = frag_sizeW;
	sizeH = frag_sizeH;
	sizeS = frag_sizeS;
	builtin_opacity = frag_builtin_opacity;
	gl_Position = builtin_matrix * vec4(vertex.x, vertex.y, 0.0, 1.0);
}
