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
	uniform float selectedHue;
};
layout(location = 0) in float coordX;
layout(location = 1) in float coordY;

vec4 getRGB(float f){
	float r;
	float g;
	float b;
	if(f < 1.0 / 6.0){ // red to yellow
		r = 1.0;
		g = 1.0 - 6.0 * (1.0 / 6.0 - f);
		b = 0.0;
	}
	else if(f < 2.0 / 6.0){ // yellow to green
		r = 6.0 * (2.0 / 6.0 - f);
		g = 1.0;
		b = 0.0;
	}
	else if(f < 3.0 / 6.0){ // green to cyan
		r = 0.0;
		g = 1.0;
		b = 1.0 - 6.0 * (3.0 / 6.0 - f);
	}
	else if(f < 4.0 / 6.0){ // cyan to blue
		r = 0.0;
		g = 6.0 * (4.0 / 6.0 - f);
		b = 1.0;
	}
	else if(f < 5.0 / 6.0){ // blue to purple
		r = 1.0 - 6.0 * (5.0 / 6.0 - f);
		g = 0.0;
		b = 1.0;
	}
	else{ // purple to red
		r = 1.0;
		g = 0.0;
		b = 6.0 * (1.0 - f);
	}
	return vec4(r, g, b, 1.0);
}

void main(){
	float newCoordX = 21.0 / 19.0 * coordX - 0.05;
	float offsetX = (newCoordX - selectedHue) * sizeW / sizeH * 2.0;
	float offsetY = (1.0 - coordY);
	if(abs(offsetX) + abs(offsetY) < 0.5){oc = getRGB(selectedHue);}
	else if(coordY > 0.8 || newCoordX < 0.0 || newCoordX > 1.0){oc = vec4(1.0, 1.0, 1.0, 0.0);}
	else{oc = getRGB(newCoordX);}
}
