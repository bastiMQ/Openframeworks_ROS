#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "Clone.h"
#include "ofxFaceTracker.h"
#include "ofxFaceTrackerThreaded.h"
#include "ofxFaceTracker2.h"
#include <iostream>
using namespace std;

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void dragEvent(ofDragInfo dragInfo);
	void loadFace(string face);

	void keyPressed(int key);

	ofxFaceTracker srcTracker;
	ofxFaceTracker camTracker;

	ofVideoGrabber cam;

	ofxFaceTracker2 camTracker2;
	ofxFaceTracker2 srcTracker2;


	ofImage src;
	
	vector<ofVec2f> srcPoints;
	vector<ofVec2f> srcPoints2;
	
	//ofMesh srcPoints_mesh;
	//vector<ofVec2f> srcPoints_mesh2;

	
	bool cloneReady;
	Clone clone;
	ofFbo srcFbo, maskFbo;

	ofDirectory faces;
	int currentFace;
};
