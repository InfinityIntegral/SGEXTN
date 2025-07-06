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
	uniform float selectedSaturation;
};
layout(location = 0) in float coordX;
layout(location = 1) in float coordY;

float computePQT(float p, float q, float t){
	if(t < 0.0){t += 1.0;}
    else if(t > 1.0){t -= 1.0;}
    if(t < 1.0 / 6.0){return (p + 6.0 * t * (q - p));}
    if(t < 0.5){return q;}
    if(t < 2.0 / 3.0){return (p + 6.0 * (2.0 / 3.0 - t) * (q - p));}
    return p;
}

vec4 getRGB(float xh, float xs){
	float r = 0.0;
	float g = 0.0;
	float b = 0.0;
	float xl = 0.5;
	if(xs == 0.0){
        r = xl;
        g = xl;
        b = xl;
    }
    else{
        float q = 0.0;
        if(xl < 0.5){q = xl * (1.0 + xs);}
        else{q = xl + xs - xl * xs;}
        float p = 2.0 * xl - q;
        r = computePQT(p, q, xh + 1.0 / 3.0);
        g = computePQT(p, q, xh);
        b = computePQT(p, q, xh - 1.0 / 3.0);
    }
	return vec4(r, g, b, 1.0);
}

void main(){
	float newCoordX = 21.0 / 19.0 * coordX - 0.05;
	float offsetX = (newCoordX - selectedSaturation) * sizeW / sizeH * 2.0;
	float offsetY = (1.0 - coordY);
	if(abs(offsetX) + abs(offsetY) < 0.5){oc = getRGB(selectedHue, selectedSaturation);}
	else if(coordY > 0.8 || newCoordX < 0.0 || newCoordX > 1.0){oc = vec4(1.0, 1.0, 1.0, 0.0);}
	else{oc = getRGB(selectedHue, newCoordX);}
}
