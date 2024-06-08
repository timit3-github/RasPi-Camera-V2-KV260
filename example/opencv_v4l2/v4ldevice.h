/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * (c) 2024 Ichiro Kawazome
 */
/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * (c) 2024 timit
 */
#ifndef _V4LDEVICE_H
#define _V4LDEVICE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <poll.h>
#include <linux/dma-heap.h>
#include <linux/videodev2.h>

#define VIDEO_DEVICE_FILE "/dev/video0"
#define DMA_HEAP_DEVICE_FILE "/dev/dma_heap/reserved"
#define CAPTURE_IMAGE_WIDTH 1920
#define CAPTURE_IMAGE_HEIGHT 1080
#define CAPTURE_IMAGE_PIXELFORMAT V4L2_PIX_FMT_RGB24
// #define CAPTURE_IMAGE_COUNT 10
#define CAPTURE_NUM_BUFFERS 4

// #include "proc_sample.h"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
using namespace cv;
using namespace std;

static int xioctl(int fd, int ioctl_code, void *parameter)
{
    int result;
    do
    {
        result = ioctl(fd, ioctl_code, parameter);
    } while ((result == -1) && (errno == EINTR));
    return result;
}

class V4L2Capture{
public:
    V4L2Capture(int width = CAPTURE_IMAGE_WIDTH, int height = CAPTURE_IMAGE_HEIGHT, int pixelformat = CAPTURE_IMAGE_PIXELFORMAT)
    {
        // proc_init(CAPTURE_IMAGE_COUNT, width, height);
        open_device();
        init_device(width, height, pixelformat);
        start_capturing();
        cvMat.create(height, width, CV_8UC3);
    };
    ~V4L2Capture() {
        stop_capturing();
        cvMat.release();
        uninit_device();
        close_device();
    };
    int read(cv::Mat& mat);
    V4L2Capture& operator>>(cv::Mat &image)
    {
        this->read(image);
        return *this;
    }
    cv::Mat cvMat;

private:
    int open_device();
    int init_device(int width = CAPTURE_IMAGE_WIDTH,
                    int height = CAPTURE_IMAGE_HEIGHT,
                    int pixelformat = CAPTURE_IMAGE_PIXELFORMAT);
    int start_capturing(void);
    int stop_capturing(void);
    int uninit_device(void);
    int close_device(void);
    int capture_frame(void);

    int video_fd = 0;
    int dma_heap_fd = 0;
    int num_planes = 0;
    int num_buffers = 0;
    struct v4l2_capability v4l2_cap;
    struct v4l2_format v4l2_fmt;
    struct v4l2_requestbuffers v4l2_reqbuf;
    struct v4l2_buffer v4l2_buf;
    enum v4l2_buf_type v4l2_buf_type;
    struct v4l2_plane v4l2_planes[CAPTURE_NUM_BUFFERS][VIDEO_MAX_PLANES];
    struct buffer
    {
        void *start;
        size_t length;
    } buffers[CAPTURE_NUM_BUFFERS][VIDEO_MAX_PLANES];
    int buf_index;
};

#endif//_V4LDEVICE_H
