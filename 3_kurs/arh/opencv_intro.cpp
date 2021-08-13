/*
Ознакомиться с программированием периферийных устройств на примере ввода данных с Web-камеры с использованием библиотеки OpenCV

gcc opencv_intro.cpp -o main -I/usr/include/opencv4/opencv -I/usr/include/opencv4 -lstdc++ -lopencv_imgcodecs -lopencv_imgproc -lopencv_core -lopencv_highgui -lopencv_shape -lopencv_videoio -Wall -Wextra -Werror 
*/
#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define ESC 27

const int FPS = 30;
const int mSec = 1000;

using namespace cv;
using namespace std;
using namespace chrono;

int main() {
	Mat frame;
	Mat gray;
	VideoCapture vid(0);

	if (!vid.isOpened())
	{
	   return -1;
    }
	while (1) 
	{
		//load origin
		
		auto readStartFrame = high_resolution_clock::now();
		
		      vid.read(frame);
		
		auto readEndFrame = high_resolution_clock::now();
		  
		  
		duration<float> readFrameTime = readEndFrame - readStartFrame;


		//load change
		
		auto changeStartFrame = high_resolution_clock::now();
		
		      cvtColor(frame, gray, CV_16U);
		
		auto changeEndFrame = high_resolution_clock::now();
		
		
		duration<float> changeFrameTime = changeEndFrame - changeStartFrame;
		

		//load imshow
		
		auto showStartFrame = high_resolution_clock::now();
		
		      imshow("origin", frame);
		      imshow("changed", gray);
		
		auto showEndFrame = high_resolution_clock::now();
		
		
		duration<float> showFrameTime = showEndFrame - showStartFrame;
		
		
		cout << "read --> " << readFrameTime.count() << "___" 
			 << "change --> " << changeFrameTime.count() << "___" 
			 << "show --> " << showFrameTime.count() << endl;
		
		char c = waitKey(mSec / FPS);   
		      
		      if (c == ESC)
		      {
		           break;
		      }
	}
}
