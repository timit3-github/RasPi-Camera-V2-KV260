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
#include "v4ldevice.h"

#define CLEAR(x) memset(&(x), 0, sizeof(x))

int V4L2Capture::open_device()
{
    //
    // 1. Open Device
    //
    video_fd = open(VIDEO_DEVICE_FILE, O_RDWR);
    if (video_fd == -1)
    {
        perror(VIDEO_DEVICE_FILE);
        return EXIT_FAILURE;
    }
    dma_heap_fd = open(DMA_HEAP_DEVICE_FILE, O_RDWR);
    if (dma_heap_fd == -1)
    {
        perror(DMA_HEAP_DEVICE_FILE);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int V4L2Capture::stop_capturing (void)
{
    //
    // 10. Stop Stream
    //
    v4l2_buf_type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
    if (xioctl(video_fd, VIDIOC_STREAMOFF, &v4l2_buf_type))
    {
        perror("VIDIOC_STREAMOFF");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int V4L2Capture::start_capturing (void)
{
    //
    // 7. Enqueue Buffers
    //
    for (int buf_index = 0; buf_index < num_buffers; buf_index++)
    {
        memset(&v4l2_buf, 0, sizeof(v4l2_buf));
        v4l2_buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
        v4l2_buf.memory = V4L2_MEMORY_DMABUF;
        v4l2_buf.index = buf_index;
        v4l2_buf.length = num_planes;
        v4l2_buf.m.planes = &v4l2_planes[buf_index][0];
        if (xioctl(video_fd, VIDIOC_QBUF, &v4l2_buf))
        {
            perror("VIDIOC_QBUF");
            return EXIT_FAILURE;
        }
    }
    //
    // 8. Start Stream
    //
    v4l2_buf_type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
    if (xioctl(video_fd, VIDIOC_STREAMON, &v4l2_buf_type))
    {
        perror("VIDIOC_STREAMON");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int V4L2Capture::uninit_device (void)
{
    //
    // 11. Unmap Buffers
    //
    for (int i = 0; i < CAPTURE_NUM_BUFFERS; i++)
    {
        for (int plane = 0; plane < num_planes; plane++)
        {
            void *start = buffers[i][plane].start;
            size_t size = buffers[i][plane].length;
            if ((start != NULL) && (start != MAP_FAILED))
            {
                if (munmap(start, size))
                {
                    perror("munmap");
                    return EXIT_FAILURE;
                }
            }
        }
    }
    return EXIT_SUCCESS;
}

int V4L2Capture::init_device ( int width, int height, int pixelformat)
{
    //
    // 2. Check Capabilities
    //
    if (xioctl(video_fd, VIDIOC_QUERYCAP, &v4l2_cap))
    {
        perror("VIDIOC_QUERYCAP");
        return EXIT_FAILURE;
    }
    if (!(v4l2_cap.capabilities & V4L2_CAP_STREAMING))
    {
        fprintf(stderr, "Not support streaming\n");
        return EXIT_FAILURE;
    }
    if (!(v4l2_cap.capabilities & V4L2_CAP_VIDEO_CAPTURE_MPLANE))
    {
        fprintf(stderr, "Not support capture multiplane\n");
        return EXIT_FAILURE;
    }
    //
    // 3. Set Capture Image Format
    //
    memset(&v4l2_fmt, 0, sizeof(v4l2_fmt));
    v4l2_fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
    v4l2_fmt.fmt.pix_mp.width = width;
    v4l2_fmt.fmt.pix_mp.height = height;
    v4l2_fmt.fmt.pix_mp.pixelformat = pixelformat;
    v4l2_fmt.fmt.pix_mp.num_planes = 1;
    if (xioctl(video_fd, VIDIOC_S_FMT, &v4l2_fmt))
    {
        perror("VIDIOC_S_FMT");
        return EXIT_FAILURE;
    }
    //
    // 4. Check Capture Image Format
    //
    memset(&v4l2_fmt, 0, sizeof(v4l2_fmt));
    v4l2_fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
    v4l2_fmt.fmt.pix_mp.width = width;
    v4l2_fmt.fmt.pix_mp.height = height;
    v4l2_fmt.fmt.pix_mp.pixelformat = pixelformat;
    v4l2_fmt.fmt.pix_mp.num_planes = 1;
    if (xioctl(video_fd, VIDIOC_G_FMT, &v4l2_fmt))
    {
        perror("VIDIOC_G_FMT");
        return EXIT_FAILURE;
    }
    if ((v4l2_fmt.fmt.pix_mp.width != width) ||
        (v4l2_fmt.fmt.pix_mp.height != height) ||
        (v4l2_fmt.fmt.pix_mp.pixelformat != pixelformat))
    {
        fprintf(stderr, "Not support format\n");
        return EXIT_FAILURE;
    }
    for (num_planes = 0; num_planes < VIDEO_MAX_PLANES; num_planes++)
        if (v4l2_fmt.fmt.pix_mp.plane_fmt[num_planes].sizeimage == 0)
            break;
    if (num_planes == 0)
    {
        fprintf(stderr, "num_planes is 0\n");
        return EXIT_FAILURE;
    }
    //
    // 5. Requst Buffers
    //
    memset(&v4l2_reqbuf, 0, sizeof(v4l2_reqbuf));
    v4l2_reqbuf.count = CAPTURE_NUM_BUFFERS;
    v4l2_reqbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
    v4l2_reqbuf.memory = V4L2_MEMORY_DMABUF;
    if (xioctl(video_fd, VIDIOC_REQBUFS, &v4l2_reqbuf))
    {
        perror("VIDIOC_REQBUFS");
        return EXIT_FAILURE;
    }
    if (v4l2_reqbuf.count < CAPTURE_NUM_BUFFERS)
    {
        fprintf(stderr, "Can not request buffer size\n");
        return EXIT_FAILURE;
    }
    //
    // 6. Prepare Buffers
    //
    num_buffers = v4l2_reqbuf.count;
    memset(&v4l2_planes[0][0], 0, sizeof(v4l2_planes));
    memset(&(buffers[0][0]), 0, sizeof(buffers));
    for (int i = 0; i < num_buffers; i++)
    {
        memset(&v4l2_buf, 0, sizeof(v4l2_buf));
        v4l2_buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
        v4l2_buf.memory = V4L2_MEMORY_DMABUF;
        v4l2_buf.index = i;
        v4l2_buf.length = num_planes;
        v4l2_buf.m.planes = &v4l2_planes[i][0];
        if (xioctl(video_fd, VIDIOC_QUERYBUF, &v4l2_buf))
        {
            perror("VIDIOC_QUERYBUF");
            return EXIT_FAILURE;
        }
        for (int plane = 0; plane < num_planes; plane++)
        {
            void *dma_heap_start;
            size_t dma_heap_size = v4l2_planes[i][plane].length;
            struct dma_heap_allocation_data alloc_data = {
                .len = dma_heap_size,
                .fd = 0,
                .fd_flags = (O_RDWR | O_CLOEXEC),
                .heap_flags = 0,
            };
            if (ioctl(dma_heap_fd, DMA_HEAP_IOCTL_ALLOC, &alloc_data))
            {
                perror("DMA_HEAP_IOCTL_ALLOC");
                return EXIT_FAILURE;
            }
            dma_heap_start = mmap(NULL,
                                  dma_heap_size,
                                  PROT_READ | PROT_WRITE,
                                  MAP_SHARED,
                                  alloc_data.fd,
                                  0);
            if (dma_heap_start == MAP_FAILED)
            {
                perror("mmap");
                return EXIT_FAILURE;
            }
            buffers[i][plane].length = dma_heap_size;
            buffers[i][plane].start = dma_heap_start;
            v4l2_planes[i][plane].m.fd = alloc_data.fd;
        }
    }

    return EXIT_SUCCESS;
}

int V4L2Capture::close_device(void)
{
    //
    // 12. Close Video Device
    //
    if (close(video_fd) < 0)
    {
        perror("Filed to close file");
        return EXIT_FAILURE;
    }
    //
    // 13. Done
    //
    // proc_complete();

    return EXIT_SUCCESS;
}

int V4L2Capture::capture_frame(void)
{
    //
    // 9. Capture Images
    //
    // for (int count = 0; count < CAPTURE_IMAGE_COUNT; count++)
    {
        // proc_start(count);
        //
        // 9.1 Wait Captured Buffer
        //
        // proc_wait_start(count);
        struct pollfd poll_fds[1];
        int poll_result;
        poll_fds[0].fd = video_fd;
        poll_fds[0].events = POLLIN;
        poll_result = poll(poll_fds, 1, 5000);
        if (poll_result == -1)
        {
            perror("Waiting for frame");
            return EXIT_FAILURE;
        }
        // proc_wait_done(count);
        //
        // 9.2 Dequeue Captured Buffer
        //
        // proc_dequeue_start(count);
        struct v4l2_plane buf_plane[VIDEO_MAX_PLANES] = {{0}};
        memset(&v4l2_buf, 0, sizeof(v4l2_buf));
        v4l2_buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
        v4l2_buf.memory = V4L2_MEMORY_DMABUF;
        v4l2_buf.length = num_planes;
        v4l2_buf.m.planes = &buf_plane[0];
        if (xioctl(video_fd, VIDIOC_DQBUF, &v4l2_buf))
        {
            perror("VIDIOC_DQBUF");
            return EXIT_FAILURE;
        }
        buf_index = v4l2_buf.index;
        // proc_dequeue_done(count);
        //
        // 9.3 Process Captured Buffer
        //
        // proc_run_start(count);
        // for (int plane = 0; plane < num_planes; plane++)
        // {
        //     void *buf_start = buffers[buf_index][plane].start;
        //     size_t buf_size = buffers[buf_index][plane].length;
        //     proc_run(count, buf_index, plane, buf_start, buf_size);
        // }
        // proc_run_done(count);
        //
        // 9.4 Enqueue Captured Buffer
        //
        // proc_enqueue_start(count);
        memset(&v4l2_buf, 0, sizeof(v4l2_buf));
        v4l2_buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
        v4l2_buf.memory = V4L2_MEMORY_DMABUF;
        v4l2_buf.index = buf_index;
        v4l2_buf.length = num_planes;
        v4l2_buf.m.planes = &v4l2_planes[buf_index][0];
        if (xioctl(video_fd, VIDIOC_QBUF, &v4l2_buf))
        {
            perror("VIDIOC_QBUF");
            return EXIT_FAILURE;
        }
        // proc_enqueue_done(count);
        // proc_done(count);
    }
    cvMat.data = (unsigned char *)buffers[buf_index][0].start;

    return EXIT_SUCCESS;
}

int V4L2Capture::read(cv::Mat &mat)
{
    capture_frame();
    // cvMat.copyTo(mat);   // deep copy
    // mat = cvMat;    // shallow copy
    cvtColor(cvMat, mat, COLOR_RGB2BGR);    // swap Red and Blue

    return mat.empty();
};
