#version 310 es
precision lowp float;
layout(location = 0) out vec4 oc;
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
layout(location = 0) in float coordX;
layout(location = 1) in float coordY;

void main(){
	float a = ((atan(coordY - center.y, coordX - center.x) / 3.14159265358979) + 1.0) * 4.0;
	float rInner = (a - floor(a)) * (radius[int(a) + 1] - 0.5 * membraneThickness) + (1.0 - (a - floor(a))) * (radius[int(a)] - 0.5 * membraneThickness);
	float rOuter = (a - floor(a)) * (radius[int(a) + 1] + 0.5 * membraneThickness) + (1.0 - (a - floor(a))) * (radius[int(a)] + 0.5 * membraneThickness);
	float distSquare = (coordX - center.x) * (coordX - center.x) + (coordY - center.y) * (coordY - center.y);
	oc = step(distSquare, rInner * rInner) * vec4(contentsColourR, contentsColourG, contentsColourB, mix(centerTransparency, edgeTransparency, distSquare / (rInner * rInner))) + step(rInner * rInner, distSquare) * step(distSquare, rOuter * rOuter) * vec4(membraneColourR, membraneColourG, membraneColourB, membraneTransparency) + step(rOuter * rOuter, distSquare) * vec4(0.0, 0.0, 0.0, 0.0);
	oc = vec4(oc.r * oc.a, oc.g * oc.a, oc.b * oc.a, oc.a);
}
