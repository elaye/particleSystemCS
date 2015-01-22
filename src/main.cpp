#include "ofMain.h"
#include "ofApp.h"

int main( ){
	ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
	// ofSetCurrentRenderer(ofGetGLProgrammableRenderer());
	
	ofSetOpenGLVersion(4,4);

	ofSetupOpenGL(1024,768,OF_WINDOW);

	ofRunApp(new ofApp());

}
