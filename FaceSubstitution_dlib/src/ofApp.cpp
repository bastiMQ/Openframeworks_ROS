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
	camTracker2.setup();
	srcTracker2.setup();
	
	camTracker.setup();
	srcTracker.setup();
	
	//usleep(1000*1000*1);
	srcTracker.setIterations(25);
	srcTracker.setAttempts(4);

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
		camTracker2.update(toCv(cam));
		camTracker.update(toCv(cam));

		cloneReady = camTracker2.getFound();

		if(cloneReady) {

			ofxFaceTracker2Instance instance = camTracker2.getInstances()[0];
			ofMesh camMesh2=  instance.getLandmarks().getImageMesh();
			
			ofMesh camMesh = camTracker.getImageMesh();
		
			camMesh.save("camTracker.mesh");
			camMesh2.save("camTracker2.mesh");
						
			camMesh.clearTexCoords();
			camMesh.addTexCoords(srcPoints2);

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
			clone.update(srcFbo.getTextureReference(), cam.getTextureReference(), maskFbo.getTextureReference());
		}
	}
}

void ofApp::draw() {
	ofSetColor(255);

	if(src.getWidth() > 0 && cloneReady) {
		clone.draw(0, 0);
	} else {
		cam.draw(0, 0);
	}

	src.draw(640, 0);
	srcTracker2.drawDebug(640, 0);

	if(!camTracker2.getFound()) {
		ofDrawBitmapStringHighlight("camera face not found", 10, 10);
	}

	ofSetColor(255);

	if(src.getWidth() == 0) {
		ofDrawBitmapStringHighlight("drag an image here", 10, 30);
	} else if(!srcTracker2.getFound()) {
		ofDrawBitmapStringHighlight("image face not found", 10, 30);
	}
	camTracker2.drawDebug();
	//camTracker2.draw();
}

void ofApp::loadFace(string face){
	cout<<"loadFace"<<endl;
	src.loadImage(face);
	cout<<"loadImage:"<<face<<endl;
	if(src.getWidth() > 0) {

	srcTracker.update(toCv(src));
	srcTracker2.update(toCv(src));
	int Ready = srcTracker2.getFound();
	
	
	if(Ready){
	ofxFaceTracker2Instance instance2 = srcTracker2.getInstances()[0];
	srcPoints = srcTracker.getImagePoints();
	srcPoints2 =  instance2.getLandmarks().getImagePoints();
	
	//srcPoints_mesh = srcTracker.getImageMesh();
	//srcPoints_mesh2 =  instance2.getLandmarks().getImageMesh();
	
	}
	}

	cout<<"loadFace_End"<<srcTracker2.getFound()<<endl;
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


			ofBuffer points2;
			points2.append(header.c_str(), header.size());
			for (int i = 0; i < srcPoints2.size(); i++) {
				string srcPoint2 = ofToString(srcPoints2[i][0]) + "\t" + ofToString(srcPoints2[i][1]) + "\n";
				points2.append(srcPoint2.c_str(), srcPoint2.size());
			}
			wrote = ofBufferToFile("points2.tsv", points2);

/*
			ofBuffer points3;
			points3.append(header.c_str(), header.size());
			for (int i = 0; i < srcPoints_mesh.size(); i++) {
				string srcPoint2 = ofToString(srcPoints_mesh[i][0]) + "\t" + ofToString(srcPoints_mesh[i][1]) + "\n";
				points3.append(srcPoint2.c_str(), srcPoint2.size());
			}
			wrote = ofBufferToFile("points3.tsv", points3);

			ofBuffer points4;
			points4.append(header.c_str(), header.size());
			for (int i = 0; i < srcPoints_mesh2.size(); i++) {
				string srcPoint2 = ofToString(srcPoints_mesh2[i][0]) + "\t" + ofToString(srcPoints_mesh2[i][1]) + "\n";
				points4.append(srcPoint2.c_str(), srcPoint2.size());
			}
			wrote = ofBufferToFile("points4.tsv", points4);
*/
				
		}
		break;
		
	}
	if(currentFace<0)currentFace=0;
	currentFace = ofClamp(currentFace,0,faces.size()-1);
	if(faces.size()!=0){
		loadFace(faces.getPath(currentFace));
	}
}
