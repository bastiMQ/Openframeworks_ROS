#pragma once
#include "ofMain.h"

#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <time.h>
#include <sys/time.h>

struct ROBOT{				//ロボットの定義
	double x;			//X座標(m)
	double y;			//Y座標(m)
	double theta;			//角度(rad)

	double v;			//入力速度(m/s)
	double w;			//入力角速度(rad/s)

	double real_x;			//X座標(m)
	double real_y;			//Y座標(m)
	double real_theta;			//角度(rad)

	double real_v;			//速度(m/s)
	double real_w;			//角速度(rad/s)

	double ac_trans_limit;		//限界加速度(m/s2)
	double ac_rot_limit;		//限界角速度(rad/s2)

	ROBOT(){
		x = 0.0;
		y = 0.0;
		theta = 0.0;

		real_x = 0.0;
		real_y = 0.0;
		real_theta = 0.0;

		v = 0.0;
		w = 0.0;

		real_v=0.0;
		real_w=0.0;

		ac_trans_limit=0.50;
		ac_rot_limit=0.50;
	}
};


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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		


		ros::NodeHandle nh;


};



