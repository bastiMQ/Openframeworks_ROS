#include "ofApp.h"

//--------------------------------------------------------------

void ofApp::mapCallback(const nav_msgs::OccupancyGridConstPtr& map)
{
      ROS_INFO("Received a %d X %d map @ %.3f m/pix",
               map->info.width,
               map->info.height,
               map->info.resolution);


	ofSetWindowShape(map->info.width, map->info.height);
	map_img.allocate(map->info.width,map->info.height, OF_IMAGE_GRAYSCALE);

	unsigned char *data = map_img.getPixels();

	for(unsigned int y = 0; y < map->info.height; y++) {
		for(unsigned int x = 0; x < map->info.width; x++) {
		unsigned int i = x + (map->info.height - y - 1) * map->info.width;
		unsigned int j = x + (y) * map->info.width;
		int pixel = (double)(100.0-map->data[i]) *2.54;
		if (map->data[i] == -1){   pixel=125;}
		data[j]=pixel;
		}
	}
	map_img.update();

}

void ofApp::setup(){
	ofSetWindowTitle("Map Edit");
	ofBackground(125,125,125);
	ofSetFrameRate(60);

	ROS_INFO("Waiting for the map");
	map_sub_ = n.subscribe("map", 1, &ofApp::mapCallback,this);


	win_scale=1.0;
}

//--------------------------------------------------------------
void ofApp::update(){
	ros::Rate r(50); 
	ros::spinOnce();
	r.sleep();

}

//--------------------------------------------------------------
void ofApp::draw(){
   // ofSetColor(0, 0, 0);

   ofScale(win_scale, win_scale);
   map_img.draw(0, 0);

    for(const std::vector<ofPoint>& line : lines){
        for(unsigned int i = 1; i < line.size(); i++){
          //ofLine(line[i-1].x, line[i-1].y, line[i].x, line[i].y);
	if(mouse_button==2){
			ofSetColor(0, 0, 0);
		}
	if(mouse_button==1){
			ofSetColor(255, 255, 255);
		}
  	  ofCircle(line[i].x, line[i].y, 5.0);
		}
	}
			ofSetColor(255, 255, 255);
}   

//--------------------------------------------------------------
void ofApp::keyPressed(int key){



  if(key == ('z' - 'a' + 1))
    {
        if(lines.size())
            lines.pop_back();
    }
    else if(key == 'c')
        lines.clear();


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    mouse_button=button;
   (lines.end()-1)->push_back(ofPoint(x*win_scale, y*win_scale));

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    mouse_button=button;
    lines.push_back(std::vector<ofPoint>());

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    mouse_button=-1;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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




