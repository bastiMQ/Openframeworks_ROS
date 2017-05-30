#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <tf/transform_broadcaster.h>

#include "ofApp.h"
struct ROBOT myrobot;

void myrobot_move(ROBOT &myrobot,double dt){
	if(dt==0.0) return;

	double ac_v=fabs(myrobot.v-myrobot.real_v)/dt;
	double ac_w=fabs(myrobot.w-myrobot.real_w)/dt;
	if(ac_v>=myrobot.ac_trans_limit)	ac_v=myrobot.ac_trans_limit;
	if(ac_w>=myrobot.ac_rot_limit)		ac_w=myrobot.ac_rot_limit;
	
	if((myrobot.v-myrobot.real_v)>=0)	myrobot.real_v+=ac_v*dt;
	else if((myrobot.v-myrobot.real_v)<0)	myrobot.real_v-=ac_v*dt;

	if((myrobot.w-myrobot.real_w)>=0)	myrobot.real_w+=ac_w*dt;
	else if((myrobot.w-myrobot.real_w)<0)	myrobot.real_w-=ac_w*dt;

	myrobot.real_x+=myrobot.real_v*sin(-myrobot.theta)*dt;
	myrobot.real_y+=myrobot.real_v*cos(-myrobot.theta)*dt;
	myrobot.real_theta-=myrobot.real_w*dt;

	double odom_slip_v=0.95;
	double odom_slip_w=0.97;

	myrobot.x+=myrobot.real_v*sin(-myrobot.theta)*dt*odom_slip_v;
	myrobot.y+=myrobot.real_v*cos(-myrobot.theta)*dt*odom_slip_v;
	myrobot.theta-=myrobot.real_w*dt*odom_slip_w;
}


 static double get_dtime(){	//時間を計測する
    struct timeval tv;
    gettimeofday(&tv, NULL);
    double n_time =tv.tv_sec + tv.tv_usec * 1e-6;
    static double o_time= n_time;
    double dt_msec=(n_time-o_time);
    o_time= n_time;
     return dt_msec;
}


void vel_Callback(const geometry_msgs::Twist &vel_msg){
    myrobot.v = vel_msg.linear.x;
    myrobot.w = -vel_msg.angular.z;
}


//--------------------------------------------------------------
void ofApp::setup(){
	ros::NodeHandle private_nh("~");

   	const std::string vel_topic= "cmd_vel";
  	ros::Subscriber cmd_vel =nh.subscribe(vel_topic, 10, vel_Callback);


}

//--------------------------------------------------------------
void ofApp::update(){

	double dt=get_dtime();
	myrobot_move(myrobot,dt);

}

//--------------------------------------------------------------
void ofApp::draw(){

	ofRect(myrobot.x,myrobot.y,10,10);


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
