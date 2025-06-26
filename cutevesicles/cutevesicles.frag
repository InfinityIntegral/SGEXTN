#version 310 es
precision highp float;
layout(location = 0) out vec4 oc;
layout(location = 0) in float builtin_opacity;
layout(location = 1) in float sizeX;
layout(location = 2) in float sizeY;
layout(location = 3) in float sizeW;
layout(location = 4) in float sizeH;
layout(location = 5) in float sizeS;
layout(binding = 1) uniform sampler2D vesiclesData;

float getVesiclesData(int n){
	int r = n % 4;
	int q = n / 4;
	if(r == 0){return texelFetch(vesiclesData, ivec2(q, 0), 0).r;}
	if(r == 1){return texelFetch(vesiclesData, ivec2(q, 0), 0).g;}
	if(r == 2){return texelFetch(vesiclesData, ivec2(q, 0), 0).b;}
	if(r == 3){return texelFetch(vesiclesData, ivec2(q, 0), 0).a;}
}

void main(){
	//oc = vec4(getVesiclesData(0), getVesiclesData(1), getVesiclesData(2), 0.5 * builtin_opacity);
	vec4 t = texelFetch(vesiclesData, ivec2(gl_FragCoord.x, 0), 0);
	oc = vec4(t.r, t.g, t.b, 1.0);
}
