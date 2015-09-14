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


		ofImage violinist;
		ofImage contrabass;

		ofImage background;
		ofImage fakeStage;

		ofImage mCenter;
		ofImage mLeft1;
		ofImage mLeft2;
		ofImage mRight1;
		ofImage mRight2;

		/////////////

		int oldalpha;
		int newalpha;

		bool raisingArms;

		bool showPos_Head = false;
		bool showPos_LHand_Shoulder = false;
		bool showAngle_Arm_Forearm = false;
		bool showAngle_Arm_Spine = false;
		bool showPos_Neck_Hip = false;

		ofSoundPlayer  synth;
};
