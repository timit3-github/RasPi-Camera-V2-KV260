GST_DEBUG=3,v4l2src*:5 \
gst-launch-1.0 -v v4l2src device=/dev/video0 num-buffers=1 ! \
	video/x-raw,width=1536,height=864 ! \
	filesink location=hoge.raw

