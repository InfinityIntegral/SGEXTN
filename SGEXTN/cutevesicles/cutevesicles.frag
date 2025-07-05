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
	uniform vec2 center[10];
	uniform float radius[90];
};
layout(location = 0) in float coordX;
layout(location = 1) in float coordY;

vec4 getColour(float x, float y, int n){
	float a = ((atan(y - center[n].y, x - center[n].x) / 3.14159265358979) + 1.0) * 4.0;
	float rInner = (a - floor(a)) * (radius[9*n + int(a) + 1] - 0.5 * membraneThickness) + (1.0 - (a - floor(a))) * (radius[9*n + int(a)] - 0.5 * membraneThickness);
	float rOuter = (a - floor(a)) * (radius[9*n + int(a) + 1] + 0.5 * membraneThickness) + (1.0 - (a - floor(a))) * (radius[9*n + int(a)] + 0.5 * membraneThickness);
	float distSquare = (x - center[n].x) * (x - center[n].x) + (y - center[n].y) * (y - center[n].y);
	vec4 returnColour = step(distSquare, rInner * rInner) * vec4(contentsColourR, contentsColourG, contentsColourB, mix(centerTransparency, edgeTransparency, distSquare / (rInner * rInner))) + step(rInner * rInner, distSquare) * step(distSquare, rOuter * rOuter) * vec4(membraneColourR, membraneColourG, membraneColourB, membraneTransparency) + step(rOuter * rOuter, distSquare) * vec4(1.0, 1.0, 1.0, 0.0);
	returnColour = vec4(returnColour.r * returnColour.a, returnColour.g * returnColour.a, returnColour.b * returnColour.a, returnColour.a);
	return returnColour;
}

vec4 blendColours(vec4 ap, vec4 bp){
	return vec4(bp.r + (1.0 - bp.a) * ap.r, bp.g + (1.0 - bp.a) * ap.g, bp.b + (1.0 - bp.a) * ap.b, bp.a + (1.0 - bp.a) * ap.a);
}

void main(){
	oc = vec4(0.0, 0.0, 0.0, 0.0);
	for(int i=0; i<10; i++){
		oc = blendColours(oc, getColour(coordX, coordY, i));
	}
}
