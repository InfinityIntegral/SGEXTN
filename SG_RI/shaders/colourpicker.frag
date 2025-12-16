#version 310 es
precision highp float;
precision highp int;
layout(std140, binding = 0) uniform SG_RI_builtin_{
    float x;
    float y;
    float width;
    float height;
    float windowWidth;
    float windowHeight;
    int offscreen;
} SG_RI_builtin;
layout(std140, binding = 1) uniform selection_{
    float hue;
    float saturation;
    float lightness;
    float transparency;
    int type;
} selection;
layout(location = 0) in vec2 vertexUnits;
layout(location = 0) out vec4 outColour;

float computePQT(float p, float q, float t){
	if(t < 0.0){t += 1.0;}
    else if(t > 1.0){t -= 1.0;}
    if(t < 1.0 / 6.0){return (p + 6.0 * t * (q - p));}
    if(t < 0.5){return q;}
    if(t < 2.0 / 3.0){return (p + 6.0 * (2.0 / 3.0 - t) * (q - p));}
    return p;
}

vec4 getRGB(float xh, float xs, float xl, float xa){
	float r = 0.0;
	float g = 0.0;
	float b = 0.0;
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
	return vec4(r, g, b, xa);
}

void main(){
    float zeroPointTwo = 0.2f * SG_RI_builtin.height / SG_RI_builtin.width;
    float selectPoint = 0.0f;
    bool addTransparencyGrid = false;
    if(selection.type == 1){selectPoint = selection.hue;}
    else if(selection.type == 2){selectPoint = selection.saturation;}
    else if(selection.type == 3){selectPoint = selection.lightness;}
    else if(selection.type == 4){selectPoint = selection.transparency;}
    if(0.5f * (1.0f - vertexUnits.y) + abs(vertexUnits.x - (zeroPointTwo + selectPoint * (1.0f - 2.0f * zeroPointTwo))) * SG_RI_builtin.width / SG_RI_builtin.height < 0.2f){
        if(selection.type == 1){outColour = getRGB(selection.hue, 1.0f, 0.5f, 1.0f);}
        else if(selection.type == 2){outColour = getRGB(selection.hue, selection.saturation, 0.5f, 1.0f);}
        else if(selection.type == 3){outColour = getRGB(selection.hue, selection.saturation, selection.lightness, 1.0f);}
        else if(selection.type == 4){
            outColour = getRGB(selection.hue, selection.saturation, selection.lightness, selection.transparency);
            addTransparencyGrid = true;
        }
    }
    else if(vertexUnits.y <= 0.8f && vertexUnits.x > zeroPointTwo && vertexUnits.x < 1.0f - zeroPointTwo){
        float x = (vertexUnits.x - zeroPointTwo) / (1.0f - 2.0f * zeroPointTwo);
        if(selection.type == 1){outColour = getRGB(x, 1.0f, 0.5f, 1.0f);}
        else if(selection.type == 2){outColour = getRGB(selection.hue, x, 0.5f, 1.0f);}
        else if(selection.type == 3){outColour = getRGB(selection.hue, selection.saturation, x, 1.0f);}
        else if(selection.type == 4){
            outColour = getRGB(selection.hue, selection.saturation, selection.lightness, x);
            addTransparencyGrid = true;
        }
    }
    else{outColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);}
    if(addTransparencyGrid == true){
        float intensity = 0.8f + 0.15f * mod(floor(5.0f * vertexUnits.x * SG_RI_builtin.width / SG_RI_builtin.height) + floor(5.0f * vertexUnits.y), 2.0f);
        outColour = vec4(outColour.a * outColour.r + (1.0f - outColour.a) * intensity, outColour.a * outColour.g + (1.0f - outColour.a) * intensity, outColour.a * outColour.b + (1.0f - outColour.a) * intensity, 1.0f);
    }
}
