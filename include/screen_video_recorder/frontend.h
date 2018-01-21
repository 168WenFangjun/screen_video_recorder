#pragma once

#include "screen_shot.h"
#include "string"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>  // Video write
#include <ros/ros.h>
#include <string.h>

#define KEY_Q 113
#define KEY_S 115

namespace screen_video_recorder{


	// Uses screen shot to record a video of the screen
	class Frontend
	{
	public:
		Frontend();
		~Frontend();

	private:
		ScreenShot screenShot_;

		// screen shot of the display
		cv::Mat img_;

		// video writer and parameters
		cv::VideoWriter videoWriter_;

		struct videoWriter_Parameters
		{
			std::string fileName;
			int fourcc;           // 4-character code used to compress frames
			double fps;           // framerate
			cv::Size frameSize;   // size of the fideo frames
			bool isColor;
		} video_writer_parameters_;

		// user input
		int key_pressed_;

		bool start_recording_ = false;


		// records the screen display and saves to video
		void recordScreen();

		// displays the screen in a small image
		void displayScreen();
                

	};



}