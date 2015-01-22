#version 430

#define EPS 0.001

uniform vec3 attractor;
uniform float strength;
uniform float drag;

struct Particle{
	vec4 pos;
	vec4 vel;
	vec4 acc;
};

layout(std430, binding=0) buffer particles{
	Particle p[];
};

layout(local_size_x = 256, local_size_y = 1, local_size_z = 1) in;

void main(){
	uint gid = gl_GlobalInvocationID.x;

	vec3 dir = p[gid].pos.xyz - attractor;

	float d = dot(dir, dir);

	p[gid].acc.xyz = -strength/(d+EPS)*dir;

	p[gid].vel += p[gid].acc;
	p[gid].vel *= drag;

	p[gid].pos += p[gid].vel;
}