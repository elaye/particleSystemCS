#pragma once

#include "ofMain.h"

#define WORK_GROUP_SIZE 256

struct Particle{
	ofVec4f pos;
	ofVec4f vel;
	ofVec4f acc;	
};

class particleManager{

	int n;

	ofShader computeShader;

	vector<Particle> particles;
	ofBufferObject particlesBuffer;

	ofVbo vbo;

	ofPoint attractor;

	ofParameter<bool> bShowAttractor;
	ofParameter<int> strength;
	ofParameter<float> drag;
	ofParameter<ofColor> color;

	public:
		ofParameterGroup parameters;
		void setup(const int n);
		void initParticles();
		void update();
		void updateAttractor();
		void draw();
};