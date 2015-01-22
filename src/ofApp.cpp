#include "ofApp.h"

void ofApp::setup(){
	ofSetVerticalSync(false);
	ofSetFrameRate(30);

	pm.setup(1024*1024);

	gui.setup();
	gui.add(pm.parameters);
	gui.add(fpsDisp.setup("Fps", ""));

	bSettings = false;
	bPause = false;
}

void ofApp::update(){
	fpsDisp = ofToString(ofGetFrameRate());

	if(!bPause){
		pm.update();
	}
}

void ofApp::draw(){
	ofBackgroundGradient(ofColor(15, 16, 37), ofColor(11, 11, 10));

	cam.begin();
		pm.draw();
	cam.end();

	if(bSettings){
		gui.draw();
	}
	else{
		ofSetColor(ofColor::white);
		ofDrawBitmapString("'s' settings\n'p' pause\n'f' fullscreen", 15, 15);
	}
}

void ofApp::keyPressed(int key){
	switch(key){
		case 'f':
			ofToggleFullscreen();
			break;
		case 's':
			bSettings = !bSettings;
			break;
		case 'p':
			bPause = !bPause;
			break;
		default:
			break;
	}
}
