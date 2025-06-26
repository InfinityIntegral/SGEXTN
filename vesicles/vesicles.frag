#version 310 es
precision highp float;
layout(location = 0) out vec4 oc;
layout(location = 0) in float qt_Opacity;
layout(location = 1) in vec2 c;
layout (location = 2) in float r;

void main(){
	float dist = (gl_FragCoord.x - c.x) * (gl_FragCoord.x - c.x) + (gl_FragCoord.y - c.y) * (gl_FragCoord.y - c.y);
	oc = vec4(0.0, 0.0, 0.0, 1.0);
}
