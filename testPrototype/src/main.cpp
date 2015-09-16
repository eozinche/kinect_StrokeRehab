#include "ofMain.h"
#include "ofApp.h"

#include "ofGLProgrammableRenderer.h"


//========================================================================
int main( ){

	ofPtr<ofBaseRenderer> renderer(new ofGLProgrammableRenderer(true));
	ofSetCurrentRenderer(renderer);

	//ofSetupOpenGL(1727, 885, OF_WINDOW);			// <-------- setup the GL context
	//ofSetupOpenGL(1920, 1320, OF_WINDOW);			
	ofSetupOpenGL(2518, 1875, OF_WINDOW);

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}


