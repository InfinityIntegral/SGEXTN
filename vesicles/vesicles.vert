#version 310 es
precision highp float;
layout(location = 0) in vec2 vertex;
layout(std140, binding = 0) uniform uvq{
	uniform mat4 qt_Matrix;
	uniform float frag_qt_Opacity;
	uniform float frag_size_x;
	uniform float frag_size_y;
	uniform float frag_size_w;
	uniform float frag_size_h;
	uniform float frag_size_s;
	uniform float frag_cx;
	uniform float frag_cy;
	uniform float frag_r;
};
layout(location = 0) out float qt_Opacity;
layout(location = 1) out float size_x;
layout(location = 2) out float size_y;
layout(location = 3) out float size_w;
layout(location = 4) out float size_h;
layout(location = 5) out float size_s;
layout(location = 6) out float cx;
layout(location = 7) out float cy;
layout(location = 8) out float r;

void main(){
	size_x = frag_size_x;
	size_y = frag_size_y;
	size_w = frag_size_w;
	size_h = frag_size_h;
	size_s = frag_size_s;
	qt_Opacity = frag_qt_Opacity;
	cx = frag_cx;
	cy = frag_cy;
	r = frag_r;
	gl_Position = qt_Matrix * vec4(vertex.x, vertex.y, 0.0, 1.0);
}
