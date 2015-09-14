#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	kinect.initSensor();
	kinect.initColorStream(true);
	kinect.initDepthStream(true);
	kinect.initBodyIndexStream();
	kinect.initSkeletonStream(true);

	//simple start
	kinect.start();
	ofDisableAlphaBlending(); //Kinect alpha channel is default 0;

	/////////////////// video input arguments////
	camWidth = 1920;	// try to grab at this size. 
	camHeight = 1080;
	//we can now get back a list of devices. 
	vector<ofVideoDevice> devices = vidGrabber.listDevices();

	for (int i = 0; i < devices.size(); i++){
		cout << devices[i].id << ": " << devices[i].deviceName;
		if (devices[i].bAvailable){
			cout << endl;
		}
		else{
			cout << " - unavailable " << endl;
		}
	}
	////////////////////////////////////////////////////////////
	vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(60);
	vidGrabber.initGrabber(camWidth, camHeight);

	videoInverted = new unsigned char[camWidth*camHeight * 3];
	videoTexture.allocate(camWidth, camHeight, GL_RGB);
	ofSetVerticalSync(true);
	
	///////////////// load images//

	ironman.loadImage("ironman.png");
	hulk.loadImage("hulk.png");
	spider.loadImage("spider.png");
	thor.loadImage("thor.png");
	
	
	
	
	/////////////// font settings
	ofTrueTypeFont::setGlobalDpi(72);

	verdana14.loadFont("verdana.ttf", 20, true, true);
	verdana14.setLineHeight(30.0f);
	//verdana14.setLetterSpacing(1.037);
	verdana14.setLetterSpacing(15.037);

	verdana30.loadFont("verdana.ttf", 40, true, true);
	verdana30.setLineHeight(34.0f);
	verdana30.setLetterSpacing(15.035);




}

//--------------------------------------------------------------
void ofApp::update(){
	kinect.update();
	ofBackground(100, 100, 100);

	vidGrabber.update();

	if (vidGrabber.isFrameNew()){
		int totalPixels = camWidth*camHeight * 3;
		unsigned char * pixels = vidGrabber.getPixels();
		for (int i = 0; i < totalPixels; i++){
			videoInverted[i] = 255 - pixels[i];
		}
		videoTexture.loadData(videoInverted, camWidth, camHeight, GL_RGB);
	}

}


//--------------------------------------------------------------
void ofApp::draw(){
	//ofBackground(255);
	ofSetColor(255);
	vidGrabber.draw(20, 20);
	videoTexture.draw(20 + camWidth, 20, camWidth, camHeight);

	//kinect.draw(0, 0);

	kinect.drawDepth(0, 0);
	//kinect.drawBodyIndex(500, 0);
	kinect.drawAllSkeletons(ofVec2f(320,240));

	float hue = fmodf(ofGetElapsedTimef() * 80, 255);

	int step = 5;
	// step through horizontally

	float wave = sin(ofGetElapsedTimef());
	

	vector<Kv2Skeleton> mySkeletons = kinect.getSkeletons();
	{
		int skeleton_count = 0;
		for (int i = 0; i < mySkeletons.size(); i++)
		{
			if (mySkeletons[i].tracked) {
				skeleton_count++;
				cout << "Drawing left hand of skeleton " << i << "\n";
				ofVec3f left_hand_pos = mySkeletons[i].joints[JointType_HandLeft].getPosition();
				ofVec3f right_hand_pos = mySkeletons[i].joints[JointType_HandRight].getPosition();
				ofVec3f head_pos = mySkeletons[i].joints[JointType_Head].getPosition();
				ofVec3f neck_pos = mySkeletons[i].joints[JointType_Neck].getPosition();
				ofVec3f hipleft_pos = mySkeletons[i].joints[JointType_HipLeft].getPosition();
				ofVec3f spinemid_pos = mySkeletons[i].joints[JointType_SpineMid].getPosition();
				ofVec3f spinebase_pos = mySkeletons[i].joints[JointType_SpineBase].getPosition();
				ofVec3f shoulderleft_pos = mySkeletons[i].joints[JointType_ShoulderLeft].getPosition();
				ofVec3f shoulderright_pos = mySkeletons[i].joints[JointType_ShoulderRight].getPosition();
				ofVec3f elbow_left_pos = mySkeletons[i].joints[JointType_ElbowLeft].getPosition();
				ofVec3f elbow_right_pos = mySkeletons[i].joints[JointType_ElbowRight].getPosition();
				ofVec3f left_knee_pos = mySkeletons[i].joints[JointType_KneeLeft].getPosition();
				ofVec3f right_knee_pos = mySkeletons[i].joints[JointType_KneeRight].getPosition();
				ofVec3f left_elbow_pos = mySkeletons[i].joints[JointType_ElbowLeft].getPosition();
				ofVec3f right_elbow_pos = mySkeletons[i].joints[JointType_ElbowRight].getPosition();


				//cout << "  x: " << left_hand_pos.x << "  y: " << left_hand_pos.y << "  z: " << left_hand_pos.z << "\n";

				ofSetColor(255);

				verdana30.drawString("Left hand pos.X    " + ofToString(left_hand_pos.x), 1400, 100 + 90 * i);
				verdana30.drawString("Left hand Pos.Y    " + ofToString(left_hand_pos.y), 1400, 125 + 90 * i);
				verdana30.drawString("Left hand Pos.Z    " + ofToString(left_hand_pos.z), 1400, 150 + 90 * i);
				verdana30.drawString("Left knee Pos.Z    " + ofToString(left_knee_pos.z), 1400, 175 + 90 * i);

				verdana30.drawString("Right hand pos.X    " + ofToString(right_hand_pos.x), 1400, 10 + 90 * i);
				verdana30.drawString("Right hand Pos.Y    " + ofToString(right_hand_pos.y), 1400, 35 + 90 * i);
				verdana30.drawString("Right hand Pos.Z    " + ofToString(right_hand_pos.z), 1400, 60 + 90 * i);
				verdana30.drawString("Right knee Pos.Z    " + ofToString(right_knee_pos.z), 1400, 85 + 90 * i);
				

				/////////////////////////////////////////////////////////////////////
				//if (left_hand_pos.y>head_pos.y) ofSetColor(255,0,0);
				//else  ofSetColor(0,255, 0);
				ofVec3f left_hand_shoulder = left_hand_pos - shoulderleft_pos;	// this is a vector point from shoulder to hand
				ofVec3f right_hand_shoulder = right_hand_pos - shoulderright_pos;	// this is a vector point from shoulder to hand

				ofVec3f left_elbow_shoulder = elbow_left_pos - shoulderleft_pos;	// this is a vector point from left shoulder to elbow
				ofVec3f right_elbow_shoulder = elbow_right_pos - shoulderright_pos;	// this is a vector point from right shoulder to elbow

				ofVec3f neck_hip = spinebase_pos - neck_pos;	// this is a vector point from neck_pos to spinebase_pos

				ofVec3f right_hand_elbow = right_hand_pos - elbow_right_pos;	// this is a vector point from shoulder to hand
				ofVec3f left_hand_elbow = left_hand_pos - elbow_left_pos;	// this is a vector point from shoulder to hand

				ofVec3f left_shoulder_elbow = shoulderleft_pos - elbow_left_pos;	// this is a vector point from shoulder to hand
				ofVec3f right_shoulder_elbow = shoulderright_pos - elbow_right_pos;	// this is a vector point from shoulder to hand

				ofVec3f left_shoulder_R_L = shoulderright_pos - shoulderleft_pos;	// this is a vector point from shoulder to hand
				ofVec3f right_shoulder_L_R = shoulderleft_pos - shoulderright_pos;	// this is a vector point from shoulder to hand


				float left_angle_hand_shoulder_with_neck_hip = left_hand_shoulder.angle(neck_hip);
				float right_angle_hand_shoulder_with_neck_hip = right_hand_shoulder.angle(neck_hip);

				float left_angle_elbow_shoulder_with_neck_hip = left_elbow_shoulder.angle(neck_hip);
				float right_angle_elbow_shoulder_with_neck_hip = right_elbow_shoulder.angle(neck_hip);

				float left_shoulder_hand_elbow_with_left_hand_pos = left_hand_elbow.angle(left_shoulder_elbow);
				float right_shoulder_hand_elbow_with_right_hand_pos = right_hand_elbow.angle(right_shoulder_elbow);
				

				float left_shoulder_right_shoulder_hand_elbow_with_right_hand_pos = right_shoulder_L_R.angle(right_hand_elbow);
				float right_shoulder_left_shoulder_hand_elbow_with_left_hand_pos = left_shoulder_R_L.angle(left_hand_elbow);


				ofSetColor(255);
				if (left_hand_pos.y>spinebase_pos.y && left_hand_pos.y<spinemid_pos.y && left_shoulder_right_shoulder_hand_elbow_with_right_hand_pos<60 && left_shoulder_right_shoulder_hand_elbow_with_right_hand_pos>30 &&
					right_hand_pos.y>spinebase_pos.y && right_hand_pos.y < spinemid_pos.y && right_shoulder_left_shoulder_hand_elbow_with_left_hand_pos < 60 && right_shoulder_left_shoulder_hand_elbow_with_left_hand_pos>30){
					ofEnableAlphaBlending();
					float wave = sin(ofGetElapsedTimef()*2.0);
					hulk.draw(500, (wave *  ofGetHeight()*.5));
					ofSetColor(10, 200, 133);
				     verdana30.drawString("Hulk Gawaaaa!!!!!", 950, 400);
		
				}
				
				else if (left_hand_pos.y > shoulderleft_pos.y && right_hand_pos.y > shoulderright_pos.y &&left_hand_pos.z < left_knee_pos.z && right_hand_pos.z < left_knee_pos.z && right_shoulder_hand_elbow_with_right_hand_pos > 130 && left_shoulder_hand_elbow_with_left_hand_pos > 130 && left_knee_pos.z < right_knee_pos.z){
					//ofSetColor(0, 255, 0);
					ofEnableAlphaBlending();
					float wave = sin(ofGetElapsedTimef()*2.0);
					spider.draw(500, (wave *  ofGetHeight()*.5));
					ofSetColor(155, 155, 200);
					verdana30.drawString("Spider Man!!! PICHEW", 950, 400);

				}
				//ofSetColor(0, 255, 0);

				else if (left_hand_pos.z > shoulderleft_pos.z && right_hand_pos.z > shoulderright_pos.z &&left_shoulder_right_shoulder_hand_elbow_with_right_hand_pos > 125 && right_shoulder_left_shoulder_hand_elbow_with_left_hand_pos > 125 && left_shoulder_right_shoulder_hand_elbow_with_right_hand_pos < 170 && right_shoulder_left_shoulder_hand_elbow_with_left_hand_pos < 170){
					ofSetColor(255);
					ofEnableAlphaBlending();
					float wave = sin(ofGetElapsedTimef()*2.0);
					ironman.draw(500, (wave * ofGetHeight()*.5));
					ofColor color = ofColor::darkSlateBlue;

					ofSetColor(color);

					verdana30.drawString("Iron Man!!! SHoooRung", 950, 400);

					
				}
				//else  ofSetColor(0, 255, 0);


				else if (right_hand_pos.y > head_pos.y && left_hand_pos.y < spinebase_pos.y){
					ofEnableAlphaBlending();
					float wave = sin(ofGetElapsedTimef()*2.0);
					thor.draw(500, (wave *  ofGetHeight()*.5));


					ofColor color = ofColor::orangeRed;

					ofSetColor(color);

					verdana30.drawString("Thor!!! kukang", 950, 400);

				}
				else  ofSetColor(0, 255, 0);
				ofDisableAlphaBlending();


				//bool righthand_is_inplace = false;
				//if (right_shoulder_hand_elbow_with_right_hand_pos < 120 && right_shoulder_hand_elbow_with_right_hand_pos>70){
				//	ofSetColor(30, 30, 255);
				//	if (left_shoulder_right_shoulder_hand_elbow_with_right_hand_pos < 110 && left_shoulder_right_shoulder_hand_elbow_with_right_hand_pos>70){
				//		righthand_is_inplace = true;
				//		ofSetColor(255, 130, 0);
				//	}
				//}


				
				

				verdana30.drawString("head pos.X    " + ofToString(head_pos.x), 800, 100 + 90 * i);
				verdana30.drawString("head Pos.Y    " + ofToString(head_pos.y), 800, 125 + 90 * i);
				verdana30.drawString("head Pos.Z    " + ofToString(head_pos.z), 800, 150 + 90 * i);
				verdana30.drawString("Right Sh to H " + ofToString(right_shoulder_hand_elbow_with_right_hand_pos), 800, 175 + 90 * i);
				verdana30.drawString("Right Sh to H-Side " + ofToString(left_shoulder_right_shoulder_hand_elbow_with_right_hand_pos), 800, 200 + 90 * i);

				/////////////////////////////////////////////////////////////////////

				
	//			ofDrawBitmapString("Left hand pos.X    " + ofToString(left_hand_pos.x), 1600, 100 + 60 * i);

		//		ofDrawBitmapString("Left hand Pos.Y    " + ofToString(left_hand_pos.y), 1600, 120 + 60 * i);
			//	ofDrawBitmapString("Left hand Pos.Z    " + ofToString(left_hand_pos.z), 1600, 140 + 60 * i);

			}
		}
		cout << skeleton_count << "\n\n\n";
	}

	ofSetColor(255);


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
