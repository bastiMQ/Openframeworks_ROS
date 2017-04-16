#pragma once

#include "ofMain.h"
#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>


class ofApp : public ofBaseApp{

	std::vector<std::vector<ofPoint> > lines;


	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);



		ofImage map_img;

		void mapCallback(const nav_msgs::OccupancyGridConstPtr& map);


	    	ros::NodeHandle n;
		ros::Subscriber map_sub_;
		ofImage image;
		int imgW, imgH;

		double win_scale;
		int mouse_button;

};