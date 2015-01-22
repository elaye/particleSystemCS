#pragma once

#include "ofMain.h"

#include "ofxGui.h"

#include "particleManager.h"

class ofApp : public ofBaseApp{

	ofEasyCam cam;

	particleManager pm;

	ofxLabel fpsDisp;

	ofxPanel gui;

	bool bSettings, bPause;

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
};
