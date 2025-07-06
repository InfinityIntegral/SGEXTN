#version 310 es
precision highp float;
layout(location = 0) in vec2 vertex;
layout(location = 1) in vec2 texcoord;
layout(std140, binding = 0) uniform uniformBuffer{
	uniform mat4 builtin_matrix;
	uniform float builtin_opacity;
	uniform float sizeX;
	uniform float sizeY;
	uniform float sizeW;
	uniform float sizeH;
};
layout(location = 0) out float coordX;
layout(location = 1) out float coordY;

void main(){
	coordX = texcoord.x;
	coordY = texcoord.y;
	gl_Position = builtin_matrix * vec4(vertex.x, vertex.y, 0.0, 1.0);
}
