#include "particleManager.h"

void particleManager::setup(const int _n){
	n = _n;

	particles.resize(n);
	initParticles();

	particlesBuffer.allocate(particles, GL_DYNAMIC_DRAW);

	vbo.setVertexBuffer(particlesBuffer, 4, sizeof(Particle));

	particlesBuffer.bindBase(GL_SHADER_STORAGE_BUFFER, 0);

	parameters.add(bShowAttractor.set("Show attractor", true));
	parameters.add(strength.set("Strength", 100, 0, 1000));
	parameters.add(drag.set("Drag", 0.0, 0.0, 1.0));
	parameters.add(color.set("Color", ofFloatColor(0.81, 0.13, 0.05, 0.15), ofFloatColor(0, 0, 0, 0), ofFloatColor(1, 1, 1, 1)));

	attractor = ofPoint(0, 0, 0);

	computeShader.setupShaderFromFile(GL_COMPUTE_SHADER, "shaders/particles_comp.glsl");
	computeShader.linkProgram();

	renderShader.load("shaders/render_vert.glsl", "shaders/render_frag.glsl");	
}

void particleManager::initParticles(){
	for(int i = 0; i < n; ++i){		
		particles[i].pos.x = ofRandomWidth() - ofGetWidth()/2.0;
		particles[i].pos.y = ofRandomHeight() - ofGetHeight()/2.0;
		particles[i].pos.z = ofRandom(-200, 200);
		particles[i].pos.w = 1.0;
		particles[i].vel.x = 0.0;
		particles[i].vel.y = 0.0;
		particles[i].vel.z = 0.0;
		particles[i].vel.w = 0.0;
		particles[i].acc.x = 0.0;
		particles[i].acc.y = 0.0;
		particles[i].acc.z = 0.0;
		particles[i].acc.w = 0.0;
	}	
}

void particleManager::update(){
	updateAttractor();
	
	computeShader.begin();
		computeShader.setUniform3f("attractor", attractor.x, attractor.y, attractor.z);
		computeShader.setUniform1f("strength", strength);
		computeShader.setUniform1f("drag", 1.0 - drag);
		computeShader.dispatchCompute(n/WORK_GROUP_SIZE, 1, 1);
		// glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);
	computeShader.end();
}

void particleManager::updateAttractor(){
	float t = ofGetElapsedTimef();
	attractor.x = 500*ofSignedNoise(0.1*t);
	attractor.y = 500*ofSignedNoise(0.3*t);
	attractor.z = 500*ofSignedNoise(0.5*t);
}

void particleManager::draw(){
	ofEnableBlendMode(OF_BLENDMODE_ADD);
		ofSetColor(color);
		renderShader.begin();
			vbo.draw(GL_POINTS, 0, n);
		renderShader.end();
	ofDisableBlendMode();

	if(bShowAttractor){
		ofSetColor(ofColor::red);
		ofDrawSphere(attractor, 10);
	}	
}