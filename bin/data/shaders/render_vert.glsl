#version 430

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;

in vec4 position;

void main(){
	gl_Position = modelViewProjectionMatrix * position;

	// Point size distance attenuation
	float dist = - (modelViewMatrix*position).z;
	gl_PointSize = clamp(500.0/dist, 1.0, 20.0);
}