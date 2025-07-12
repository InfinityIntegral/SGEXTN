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
	uniform float sizeS;
	uniform float membraneColourR;
	uniform float membraneColourG;
	uniform float membraneColourB;
	uniform float contentsColourR;
	uniform float contentsColourG;
	uniform float contentsColourB;
	uniform float centerTransparency;
	uniform float edgeTransparency;
	uniform float membraneTransparency;
	uniform float membraneThickness;
	uniform vec2 center;
	uniform float radius[9];
};
layout(location = 0) out float coordX;
layout(location = 1) out float coordY;

void main(){
	coordX = texcoord.x;
	coordY = texcoord.y * sizeH / sizeW;
	gl_Position = builtin_matrix * vec4(vertex.x, vertex.y, 0.0, 1.0);
}
