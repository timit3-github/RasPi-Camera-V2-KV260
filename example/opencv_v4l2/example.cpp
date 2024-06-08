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
#include <time.h>
#include "example.h"

int main(int argc, char** argv)
{
    bool show_fps = 1;
    bool show_osd = 0;
    int osd_timer = OSD_TIMER_FRAMES;
    Scalar ost_color = OSD_COLOR;
    String osd_str;
    time_t t;
    struct tm tm;

    cout << "Built with OpenCV " << CV_VERSION << endl;

#ifdef ENABLE_FULLSCREEN
    namedWindow(WINDOW_NAME, WINDOW_NORMAL | WINDOW_KEEPRATIO | WINDOW_GUI_NORMAL);
    setWindowProperty(WINDOW_NAME, WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
#else
    namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE | WINDOW_KEEPRATIO | WINDOW_GUI_NORMAL);
#endif

#ifdef FPS_CHECK
    float fps = 0.0;
    TickMeter meter;
    int fcount = 0;
    meter.start();
#endif

    V4L2Capture cap;
    Mat image;

    while(1)
    {
        cap >> image;

#ifdef FPS_CHECK
        if (++fcount >= FPS_FRAMES)
        {
            meter.stop();
            fps = 1000.0 / meter.getTimeMilli() * fcount;
            if (!show_fps)
                printf("%3.1f fps\n", fps);
            fcount = 0;
            meter.reset();
            meter.start();
        }
        if(show_fps)
            putText(image, format("%3.1f fps", fps), Point(20, 50),
            FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255), 1, LINE_AA);
#endif

        if(show_osd)
            putText(image, osd_str, Point(200, 50),
            FONT_HERSHEY_COMPLEX, 1, ost_color, 1, LINE_AA);

        imshow(WINDOW_NAME, image);

        auto key = waitKey(1);
        if( key == 'q' || key == 27 )   //q or ESC
        {
            break;
        }
        else if( key == 's' )
        {
            t = time(NULL);
            localtime_r(&t, &tm);
            char date[64];
            strftime(date, sizeof(date), "%Y%m%d-%H%M%S.png", localtime(&t));
            cv::imwrite(date, image);
            osd_str = format("%s captured!", date);
            show_osd = 1;
            osd_timer = OSD_TIMER_FRAMES;
        }
        else if( key == 'f' )
        {
            if(show_fps == 0)
                show_fps = 1;
            else
                show_fps = 0;
        }

        if(show_osd == 1 && osd_timer > 0)
        {
            osd_timer--;
        }
        else
        {
            show_osd = 0;
        }
    }
    return 0;
}
