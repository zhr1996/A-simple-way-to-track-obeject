#include <stdio.h>
#include <iostream>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;


int main(int argc, char* argv[])
{
	double Width, Height;
	int HMAX = 255;
	int HMIN = 100;
	int SMAX = 255;
	int SMIN = 100;
	int VMAX = 255;
	int VMIN = 100;
	Mat	 frame;
	VideoCapture cap(0);         //open the default video camera
	if (!cap.isOpened())
	{
		cout << "The camera is not working" << endl;
		return -1;
	}
	Width = cap.get(CV_CAP_PROP_FRAME_WIDTH);      //get the width of the video
	Height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);    //get the height of the video

	//createTrackbar()
	String window_name1 = "RGB_picture";
	String window_name2 = "HSV_pictrue";
	String window_name3 = "Trackbars";
	String window_name4 = "Threshold";
	String window_name5 = "Object_Tracking";
	namedWindow(window_name1);
	namedWindow(window_name2);
	namedWindow(window_name3);
	namedWindow(window_name4);
	namedWindow(window_name5);
	createTrackbar("HMAX", window_name3, &HMAX, 255);
	createTrackbar("HMIN", window_name3, &HMIN, 255);
	createTrackbar("SMAX", window_name3, &SMAX, 255);
	createTrackbar("SMIN", window_name3, &SMIN, 255);
	createTrackbar("VMAX", window_name3, &VMAX, 255);
	createTrackbar("VMIN", window_name3, &VMIN, 255);


	while (true)
	{
		Mat HSV_picture;
		Mat Threshold;
		
	
		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		cap.read(frame);
		Mat Object_Tracking;
		Mat canny_output;
		Mat temp;

		cvtColor(frame, HSV_picture,CV_BGR2HSV);
		inRange(HSV_picture, Scalar(HMIN, SMIN, VMIN), Scalar(HMAX, SMAX, VMAX), Threshold);
		imshow(window_name1, frame);
		imshow(window_name2, HSV_picture);
		Mat kernel1 = getStructuringElement(MORPH_RECT, Size(3, 3),Point(0,0));
		Mat kernel2 = getStructuringElement(MORPH_RECT, Size(8, 8), Point(0, 0));

		erode(Threshold, Threshold, kernel1, Point(0, 0));
		erode(Threshold, Threshold, kernel1, Point(0, 0));

		dilate(Threshold, Threshold, kernel2,Point(0, 0));
		dilate(Threshold, Threshold, kernel2, Point(0, 0));

		Threshold.copyTo(temp);
		frame.copyTo(Object_Tracking);
		Canny(temp, canny_output, 100, 200, 3);
		findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
		for (int i = 0; i < contours.size(); i++)
		{
			drawContours(Object_Tracking, contours, i, Scalar(0,0,255),3);
		}
		imshow(window_name4, Threshold);
		imshow(window_name5, Object_Tracking);
		if (waitKey(10) == 27)
		{
			cout << "The Window has been closed" << endl;
			break;
		}
		
	}
	return 0;


	
}
