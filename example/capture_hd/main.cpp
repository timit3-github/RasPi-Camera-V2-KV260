/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * (c) 2024 timit
 */
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#define WINDOWNAME "imx708"
#define ENABLE_FULLSCREEN

int main(int argc, char** argv)
{

    //cv::VideoCapture cap("v4l2src device=/dev/video0 ! video/x-raw, width=2304, height=1296 ! appsink sync=false", cv::CAP_GSTREAMER);
    cv::VideoCapture cap("v4l2src device=/dev/video0 ! video/x-raw, width=1920, height=1080 ! appsink sync=false", cv::CAP_GSTREAMER);
    cv::Mat frame;

#ifdef ENABLE_FULLSCREEN
    cv::namedWindow(WINDOWNAME, cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO | cv::WINDOW_GUI_NORMAL);
    cv::setWindowProperty(WINDOWNAME, cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
#else
    cv::namedWindow(WINDOWNAME, cv::WINDOW_AUTOSIZE | cv::WINDOW_KEEPRATIO | cv::WINDOW_GUI_NORMAL);
#endif

    while (1) {
        cap >> frame;
        cv::imshow(WINDOWNAME, frame);
        auto key = cv::waitKey(1);
        if (key == 'q' || key == 27)
            break;
    }
	
    return 0;
}
