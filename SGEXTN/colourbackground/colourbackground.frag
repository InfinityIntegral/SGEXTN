#version 310 es
precision highp float;
layout(location = 0) out vec4 oc;
layout(std140, binding = 0) uniform uniformBuffer{
	uniform mat4 builtin_matrix;
	uniform float builtin_opacity;
	uniform float sizeX;
	uniform float sizeY;
	uniform float sizeW;
	uniform float sizeH;
};
layout(location = 0) in float coordX;
layout(location = 1) in float coordY;

void main(){
	int i = int(coordY * 4.0) - int(coordX * sizeW / sizeH * 4.0);
	if(i % 2 == 0){oc = vec4(0.0, 0.0, 0.0, 1.0);}
	else{oc = vec4(1.0, 1.0, 1.0, 1.0);}
}
