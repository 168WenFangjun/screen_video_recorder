#include "frontend.h"


namespace screen_video_recorder{



Frontend::Frontend()
{

	ros::NodeHandle nh_private("~");

	screenShot_.setWidth(screenShot_.getWidth()/2);

	nh_private.param<std::string>("filename", video_writer_parameters_.fileName,"video.AVI");

	// get video writer parameters.
	video_writer_parameters_.fourcc = cv::VideoWriter::fourcc('H','2','6','4');
	video_writer_parameters_.fps = (double) (screenShot_.getFPS()/2.0);
	video_writer_parameters_.frameSize = cv::Size(screenShot_.getWidth(), screenShot_.getHeight());
	video_writer_parameters_.isColor = true;

	// open the video writer
	videoWriter_.open(video_writer_parameters_.fileName,
					video_writer_parameters_.fourcc,
					video_writer_parameters_.fps,
					video_writer_parameters_.frameSize,
					video_writer_parameters_.isColor);

	// videoWriter_.open("video.avi",  -1, 29, cv::Size(480, 640));

	// printf("codec %i \n", (int)videoWriter_.fourcc);

	if(!videoWriter_.isOpened())
	{
		ROS_WARN("SVR frontend: Could not open video writer\n");
	}

	//Display image in this window
	cv::namedWindow("screenShot",0);  
	cv::moveWindow("screenShot",screenShot_.getWidth()*(1-1.1/6.0),screenShot_.getHeight()*(1-1.1/6.0));
	cv::resizeWindow("screenShot",screenShot_.getWidth()/6,screenShot_.getHeight()/6);

	// blank  image until recording is started
	img_ = cv::Mat::zeros(cv::Size(screenShot_.getWidth(),screenShot_.getHeight()),16);

	recordScreen();
}

void Frontend::recordScreen(){

	// the loop will execute at this rate
	ros::Rate r( (video_writer_parameters_.fps) );

	// continuously record video if video writer is open 
	// and ros is ok and user did not press q
	while(ros::ok() && videoWriter_.isOpened() && key_pressed_ !=KEY_Q)
	{

		// printf("cols %i", img_.cols);
		if(start_recording_)
		{
			// get the image
			screenShot_.getImage(img_);

			// convert image
			cv::cvtColor(img_,img_,cv::COLOR_BGRA2BGR,3);

			// write the image
			videoWriter_.write(img_);



			
		}

		// display the image on the screen
		displayScreen();

		// check for ros callbacks
		ros::spinOnce();

		// sleep for fps hz
		r.sleep();

	}

	ROS_INFO("Finished Recording Video");


}

Frontend::~Frontend(){
	videoWriter_.release();
}

void Frontend::displayScreen()
{
	cv::imshow("screenShot", img_);

	key_pressed_ = cv::waitKey(1);

	// start or stop the recording
	if(key_pressed_ == KEY_S )
	{
		if(start_recording_)
			ROS_INFO("Stopping video recording.");
		else
			ROS_INFO("Starting video recording.");
		start_recording_ = !start_recording_;
	}
}

}
