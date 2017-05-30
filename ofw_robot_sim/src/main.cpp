#include "ofMain.h"
#include "ofApp.h"


//========================================================================
int main(int argc, char *argv[]){
      ros::init(argc, argv, "ros_myrobot");  // ROSノード名の初期化

	ofSetupOpenGL(640,640,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
