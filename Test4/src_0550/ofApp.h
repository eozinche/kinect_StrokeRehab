#pragma once

#include "ofMain.h"
#include "ofxKinectCommonBridge.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		ofxKinectCommonBridge kinect;
		ofShader yuvRGBShader;
		ofPlanePrimitive plane;

		bool bFirst;
		string typeStr;

		ofTrueTypeFont  franklinBook14;
		ofTrueTypeFont	verdana14;
		ofTrueTypeFont	verdana30;
		ofTrueTypeFont	verdana60;
		float hue = fmodf(ofGetElapsedTimef() * 80, 255);
		//// 08/25/2014 -- adding videoGrabber camera input///////////////////
		ofVideoGrabber 		vidGrabber;
		unsigned char * 	videoInverted;
		ofTexture			videoTexture;
		int 				camWidth;
		int 				camHeight;
		////// adding images////////////////////////////////////////

		ofImage ironman;
		ofImage hulk;
		ofImage spider;
		ofImage thor;





};
