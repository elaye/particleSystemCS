#version 430

uniform vec4 globalColor;

out vec4 color;

void main(){
	vec2 location = gl_PointCoord - vec2(0.5, 0.5);
	float d = dot(location, location);
	if(d > (0.25)) discard;
	
	color = globalColor;
}