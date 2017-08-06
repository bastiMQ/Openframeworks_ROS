#include "ofApp.h"

using namespace ofxCv;

void ofApp::setup() {
#ifdef TARGET_OSX
	//ofSetDataPathRoot("../data/");
#endif
	ofSetVerticalSync(true);
	cloneReady = false;
	cam.initGrabber(640, 480);
	clone.setup(cam.getWidth(), cam.getHeight());
	ofFbo::Settings settings;
	settings.width = cam.getWidth();
	settings.height = cam.getHeight();
	maskFbo.allocate(settings);
	srcFbo.allocate(settings);
	camTracker.setup();
	srcTracker.setup();
	
	//iterations(10) // [1-25] 1 is fast and inaccurate, 25 is slow and accurate
	//clamp(3) // [0-4] 1 gives a very loose fit, 4 gives a very tight fit
	//tolerance(.01) // [.01-1] match tolerance
	//attempts(1) // [1-4] 1 is fast and may not find faces, 4 is slow but will find faces
	//failed(true)
	//fcheck(true) // check for whether the tracking failed
	//frameSkip(-1) // how often to skip frames
	srcTracker.setIterations(2);
	srcTracker.setAttempts(4);
	srcTracker.setClamp(1);
	srcTracker.setTolerance(0.01);

	faces.allowExt("jpg");
	faces.allowExt("png");
	faces.listDir("faces");
	currentFace = 0;
	if(faces.size()!=0){
		loadFace(faces.getPath(currentFace));
	}
}

void ofApp::update() {
	cam.update();
	if(cam.isFrameNew()) {
		camTracker.update(toCv(cam));
		
		cloneReady = camTracker.getFound();
		if(cloneReady) {
			ofMesh camMesh = camTracker.getImageMesh();
			camMesh.clearTexCoords();
			camMesh.addTexCoords(srcPoints);
			
			maskFbo.begin();
			ofClear(0, 255);
			camMesh.draw();
			maskFbo.end();
			
			srcFbo.begin();
			ofClear(0, 255);
			src.bind();
			camMesh.draw();
			src.unbind();
			srcFbo.end();
			
			clone.setStrength(16);
			clone.update(srcFbo.getTextureReference(), cam.getTextureReference(),maskFbo.getTextureReference());
		}
		
	//	int cloneReady2 = srcTracker.getFound();
	//	if(cloneReady2) {
	//	srcTracker.update(toCv(src));
	//	srcPoints = srcTracker.getImagePoints();
	//	}
	}

	
}

void ofApp::draw() {
	ofSetColor(255);
	
	src.draw(0, 0);
	srcTracker.draw();
		
	if(src.getWidth() > 0 && cloneReady) {
		clone.draw(320, 0);
	} else {
		cam.draw(320, 0);
	//	clone.draw(320, 0);
	}

	
	if(!camTracker.getFound()) {
	ofDrawBitmapStringHighlight("camera face not found", 10, 10);
	}
	if(src.getWidth() == 0) {
	ofDrawBitmapStringHighlight("drag an image here", 10, 30);
	} else if(!srcTracker.getFound()) {
	ofDrawBitmapStringHighlight("image face not found", 10, 30);
	}
	
	//camTracker.draw();
	
	
}

void ofApp::loadFace(string face){
	src.loadImage(face);
	int w = src.getWidth();
	int h = src.getHeight();
    	src.resize(320.0,320.0*h/w);
	
	
	if(src.getWidth() > 0) {
	srcTracker.update(toCv(src));
	int cloneReady2 = srcTracker.getFound();
		if(cloneReady2) {
		srcPoints = srcTracker.getImagePoints();
		}
	}
}

void ofApp::dragEvent(ofDragInfo dragInfo) {
	loadFace(dragInfo.files[0]);
}

void ofApp::keyPressed(int key){
	switch(key){
	case OF_KEY_UP:
		currentFace++;
		break;
	case OF_KEY_DOWN:
		currentFace--;
		break;

	case 's': // Save points to points.tsv.
		if (srcPoints.size() > 0) {
			ofBuffer points;
			string header = "x\ty\n";
			points.append(header.c_str(), header.size());
			
			for (int i = 0; i < srcPoints.size(); i++) {
				string srcPoint = ofToString(srcPoints[i][0]) + "\t" + ofToString(srcPoints[i][1]) + "\n";
				points.append(srcPoint.c_str(), srcPoint.size());
			}
			
			bool wrote = ofBufferToFile("points.tsv", points);
			cout << "Wrote points.tsv." << endl;
		}
		break;
		
	}
	if(currentFace<0)currentFace=0;
	currentFace = ofClamp(currentFace,0,faces.size()-1);
	if(faces.size()!=0){
		loadFace(faces.getPath(currentFace));
	}
}
