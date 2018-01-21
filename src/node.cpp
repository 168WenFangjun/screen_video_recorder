#include <ros/ros.h>
#include "frontend.h"

int main(int argc, char** argv){
	// start node
	ros::init(argc, argv, "screen_video_recorder_node");


	screen_video_recorder::Frontend frontend;


	// ros::spin();
	return 0;
}