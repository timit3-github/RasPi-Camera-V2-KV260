//#include <opencv2/opencv.hpp>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

int main(int argc, char** argv)
{

    cv::VideoCapture cap("v4l2src device=/dev/video0 ! video/x-raw, width=1536, height=864 ! appsink sync=false", cv::CAP_GSTREAMER);
    cv::Mat frame;

    cap >> frame;
    cv::imwrite("hoge.png", frame);
	
    return 0;
}
