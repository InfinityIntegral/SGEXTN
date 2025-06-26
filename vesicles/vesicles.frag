#version 310 es
precision highp float;
layout(location = 0) out vec4 oc;
layout(location = 0) in float qt_Opacity;
layout(location = 1) in float size_x;
layout(location = 2) in float size_y;
layout(location = 3) in float size_w;
layout(location = 4) in float size_h;
layout(location = 5) in float size_s;
layout(location = 6) in float cx;
layout(location = 7) in float cy;
layout(location = 8) in float r;

void main(){
	float x = cx * size_s + size_x;
	float y = cy * size_s + size_y;
	float inCircle = (gl_FragCoord.x - x) * (gl_FragCoord.x - x) + (gl_FragCoord.y - y) * (gl_FragCoord.y - y) - r * r * size_s * size_s;
	if(inCircle <= 0.0){oc = vec4(0.0, 0.0, 0.0, qt_Opacity * 0.5);}
	else{oc = vec4(1.0, 1.0, 1.0, 0.0);}
}
