Raspberry Pi Camera V3 for Kv260
====================================================================================

Overvier
------------------------------------------------------------------------------------

### Intrduction

This repository provides PL(Programmable Logic) for using the Raspberry Pi Camera-V3 with the KV260.
The PL and Device Tree provided in this repository is based on the blog shown at the following URL.

  * ~https://forxai.konicaminolta.com/blog/30~ -> https://forxai.konicaminolta.com/blog/pdf/030.pdf
  * ~https://forxai.konicaminolta.com/blog/31~ -> https://forxai.konicaminolta.com/blog/pdf/031.pdf

I would like to take this opportunity to thank them.

### Requirement

* Board: 
  - Kv260
* OS: 
  - https://github.com/ikwzm/ZynqMP-FPGA-Ubuntu22.04-Desktop

Current Status
------------------------------------------------------------------------------------

* Build Bitstream file : Success
* Install Device tree  : Success
* Setup video4linux    : Success
* Capture by camera    : Success


Build Bitstream file
------------------------------------------------------------------------------------

[Build raspi-camera-v3-kv260-w8x1-hp0.bin](./fpga/raspi-camera-v3-w8x1-hp0/Readme.md)

Install Bitstream and Device Tree
------------------------------------------------------------------------------------

### Decompress raspi-camera-v3-kv260-w8x1-hp0.bin.gz to raspi-camera-v3-kv260-w8x1-hp0.bin

```console
shell$ gzip -d fpga/raspi-camera-v3-w8x1-hp0/raspi-camera-v3-kv260-w8x1-hp0.bin.gz
```

### Copy fpga/raspi-camera-v3-w8x1-hp0/raspi-camera-v3-kv260-w8x1-hp0.bin to /lib/firmware

```console
shell$ sudo cp fpga/raspi-camera-v3-w8x1-hp0/raspi-camera-v3-kv260-w8x1-hp0.bin /lib/firmware
```

### Copy kernel_module/imx708.ko to /lib/modules/6.1.70-zynqmp-fpga-trial/kernel/drivers/media/i2c
```console
shell$ sudo cp kernel_module/imx708.ko /lib/modules/6.1.70-zynqmp-fpga-trial/kernel/drivers/media/i2c
```

### Load Device Tree Overlay

```console
shell$ sudo devicetrees/dtbo-config -v -i --dts devicetrees/raspi-camera-v3-kv260-w8x1-hp0.dts
## devicetrees/dtbo-config: install raspi-camera-v3-kv260-w8x1-hp0 dts devicetrees/raspi-camera-v3-kv260-w8x1-hp0.dts
mkdir /config/device-tree/overlays//raspi-camera-v3-kv260-w8x1-hp0
cat devicetrees/raspi-camera-v3-kv260-w8x1-hp0.dts | dtc -@ -I dts -O dtb > /config/device-tree/overlays//raspi-camera-v3-kv260-w8x1-hp0/dtbo
<stdin>:359.39-369.7: Warning (graph_child_address): /fragment@3/__overlay__/vcap_v_proc_ss_scaler/ports: graph node has single child node 'port@0', #address-cells/#size-cells are not necessary
```

```console
shell$ dmesg | tail -75
[ 9376.072284] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/afi0
[ 9376.081771] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/clocking0
[ 9376.091692] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/clocking1
[ 9376.101612] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/overlay2
[ 9376.111446] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/imx708_vana
[ 9376.121541] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/imx708_vana2
[ 9376.131726] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/imx708_vdig
[ 9376.141818] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/imx708_vddl
[ 9376.151913] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/imx708_clk
[ 9376.161928] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/overlay3
[ 9376.171767] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/axi_iic_0
[ 9376.181686] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/iic_mux_0
[ 9376.191610] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/isa0_i2c0
[ 9376.201530] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/isa1_i2c1
[ 9376.211451] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/rpi_i2c2
[ 9376.221285] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/imx708
[ 9376.230947] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/imx708_0
[ 9376.240781] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/misc_clk_0
[ 9376.250789] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/mipi_csi2_rx_subsyst_0
[ 9376.261838] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/mipi_csi_portsmipi_csi2_rx_subsyst_0
[ 9376.274104] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/mipi_csi_port1mipi_csi2_rx_subsyst_0
[ 9376.286373] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/mipi_csirx_outmipi_csi2_rx_subsyst_0
[ 9376.298643] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/mipi_csi_port0mipi_csi2_rx_subsyst_0
[ 9376.310908] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/mipi_csi_inmipi_csi2_rx_subsyst_0
[ 9376.322912] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/misc_clk_1
[ 9376.332920] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/v_demosaic_0
[ 9376.343102] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/demosaic_portsv_demosaic_0
[ 9376.354507] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/demosaic_port1v_demosaic_0
[ 9376.365903] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/demo_outv_demosaic_0
[ 9376.376780] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/demosaic_port0v_demosaic_0
[ 9376.388177] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/v_demosaic_0mipi_csi2_rx_subsyst_0
[ 9376.400268] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/v_frmbuf_wr_0
[ 9376.410541] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/v_gamma_lut_0
[ 9376.420806] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/gamma_portsv_gamma_lut_0
[ 9376.432030] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/gamma_port1v_gamma_lut_0
[ 9376.443260] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/gamma_outv_gamma_lut_0
[ 9376.454354] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/gamma_port0v_gamma_lut_0
[ 9376.465611] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/v_gamma_lut_0v_demosaic_0
[ 9376.476924] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/v_proc_ss_csc
[ 9376.487192] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/csc_portsv_proc_ss_csc
[ 9376.498241] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/csc_port1v_proc_ss_csc
[ 9376.509290] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/csc_outv_proc_ss_csc
[ 9376.520169] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/csc_port0v_proc_ss_csc
[ 9376.531216] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/v_proc_ss_cscv_gamma_lut_0
[ 9376.542620] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/v_proc_ss_scaler
[ 9376.553152] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/scaler_portsv_proc_ss_scaler
[ 9376.564722] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/scaler_port1v_proc_ss_scaler
[ 9376.576292] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/sca_outv_proc_ss_scaler
[ 9376.587429] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/scaler_port0v_proc_ss_scaler
[ 9376.598999] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/v_proc_ss_scalerv_proc_ss_csc
[ 9376.610656] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/vcap_portsv_proc_ss_scaler
[ 9376.622053] OF: overlay: WARNING: memory leak will occur if overlay removed, property: /__symbols__/v_frmbuf_wr_0v_proc_ss_scaler
[ 9376.744354] xilinx-frmbuf a0020000.v_frmbuf_wr: Xilinx AXI frmbuf DMA_DEV_TO_MEM
[ 9376.744476] xilinx-frmbuf a0020000.v_frmbuf_wr: Xilinx AXI FrameBuffer Engine Driver Probed!!
[ 9376.745161] i2c i2c-3: Added multiplexed i2c bus 4
[ 9376.745645] i2c i2c-3: Added multiplexed i2c bus 5
[ 9376.746465] i2c i2c-3: Added multiplexed i2c bus 6
[ 9376.748773] i2c i2c-3: Added multiplexed i2c bus 7
[ 9376.749941] pca954x 3-0074: registered 4 multiplexed busses for I2C switch pca9546
[ 9376.760121] xilinx-demosaic a0010000.v_demosaic: Xilinx Video Demosaic Probe Successful
[ 9376.761076] xilinx-gamma-lut a0030000.v_gamma_lut: Xilinx 10-bit Video Gamma Correction LUT registered
[ 9376.761540] xilinx-vpss-csc a0040000.v_proc_ss_csc: VPSS CSC 8-bit Color Depth Probe Successful
[ 9376.761809] imx708 6-001a: supply VANA not found, using dummy regulator
[ 9376.761931] imx708 6-001a: supply VDIG not found, using dummy regulator
[ 9376.761965] imx708 6-001a: supply VDDL not found, using dummy regulator
[ 9376.771097] imx708 6-001a: camera module ID 0x0302
[ 9376.771835] xilinx-vpss-scaler a0080000.v_proc_ss_scaler: Num Hori Taps 6
[ 9376.771849] xilinx-vpss-scaler a0080000.v_proc_ss_scaler: Num Vert Taps 6
[ 9376.771855] xilinx-vpss-scaler a0080000.v_proc_ss_scaler: VPSS Scaler Probe Successful
[ 9376.772598] xilinx-video axi:vcap_v_proc_ss_scaler: Entity type for entity a0080000.v_proc_ss_scaler was not initialized!
[ 9376.772668] xilinx-video axi:vcap_v_proc_ss_scaler: Entity type for entity a0040000.v_proc_ss_csc was not initialized!
[ 9376.772680] xilinx-video axi:vcap_v_proc_ss_scaler: Entity type for entity a0030000.v_gamma_lut was not initialized!
[ 9376.772688] xilinx-video axi:vcap_v_proc_ss_scaler: Entity type for entity a0010000.v_demosaic was not initialized!
[ 9376.772696] xilinx-video axi:vcap_v_proc_ss_scaler: Entity type for entity 80002000.mipi_csi2_rx_subsystem was not initialized!
[ 9376.791079] xilinx-video axi:vcap_v_proc_ss_scaler: device registered
```

Setup video4linux
------------------------------------------------------------------------------------

### Requirement

```console
shell$ sudo apt install -y yavta
shell$ sudo apt install -y v4l-utils
```

### Run tools/setup.sh

Rewrite `v4l2_entry_imx708` in [tools/setup.sh](tools/setup.sh) before execution according to the specifications of the camera to be used.

|             | Normal filter | No-IR filter       |
| ----        | ----          | ----               |
| Normal lens | `imx708`      | `imx708_noir`      |
| Wide lens   | `imx708_wide` | `imx708_wide_noir` |

```console
shell$ sudo sh tools/setup.sh -s -v
# mipi_csi2_rx:
#   entry  : 80002000.mipi_csi2_rx_subsystem
#   device : /dev/v4l-subdev5
# v_demosaic:
#   entry  : a0010000.v_demosaic
#   device : /dev/v4l-subdev4
# v_gamma_lut:
#   entry  : a0030000.v_gamma_lut
#   device : /dev/v4l-subdev3
# v_proc_ss_csc:
#   entry  : a0040000.v_proc_ss_csc
#   device : /dev/v4l-subdev2
# v_proc_ss_scaler:
#   entry  : a0080000.v_proc_ss_scaler
#   device : /dev/v4l-subdev0
### SONY IMX708 Sensor ###
media-ctl -d /dev/media0 --set-v4l2 '"imx708_wide":0 [fmt:SRGGB10_1X10/1536x864]'
### MIPI CSI2-Rx ###
media-ctl -d /dev/media0 --set-v4l2 '"80002000.mipi_csi2_rx_subsystem":0 [fmt:SRGGB10_1X10/1536x864 field:none]'
media-ctl -d /dev/media0 --set-v4l2 '"80002000.mipi_csi2_rx_subsystem":1 [fmt:SRGGB10_1X10/1536x864 field:none]'
### Demosaic IP subdev2 ###
media-ctl -d /dev/media0 --set-v4l2 '"a0010000.v_demosaic":0 [fmt:SRGGB10_1X10/1536x864 field:none]'
media-ctl -d /dev/media0 --set-v4l2 '"a0010000.v_demosaic":1 [fmt:RBG888_1X24/1536x864 field:none]'
### Gamma LUT IP ###
media-ctl -d /dev/media0 --set-v4l2 '"a0030000.v_gamma_lut":0 [fmt:RBG888_1X24/1536x864 field:none]'
media-ctl -d /dev/media0 --set-v4l2 '"a0030000.v_gamma_lut":1 [fmt:RBG888_1X24/1536x864 field:none]'
### VPSS: Color Space Conversion (CSC) Only ###
media-ctl -d /dev/media0 --set-v4l2 '"a0040000.v_proc_ss_csc":0 [fmt:RBG888_1X24/1536x864 field:none]'
media-ctl -d /dev/media0 --set-v4l2 '"a0040000.v_proc_ss_csc":1 [fmt:RBG888_1X24/1536x864 field:none]'
### VPSS: Scaler Only with CSC ###
media-ctl -d /dev/media0 --set-v4l2 '"a0080000.v_proc_ss_scaler":0 [fmt:RBG888_1X24/1536x864 field:none]'
media-ctl -d /dev/media0 --set-v4l2 '"a0080000.v_proc_ss_scaler":1 [fmt:RBG888_1X24/1536x864 field:none]'
yavta --no-query -w '0x0098c9c1 5' /dev/v4l-subdev3
Device /dev/v4l-subdev3 opened.
Control 0x0098c9c1 set to 5, is 5
yavta --no-query -w '0x0098c9c2 5' /dev/v4l-subdev3
Device /dev/v4l-subdev3 opened.
Control 0x0098c9c2 set to 5, is 5
yavta --no-query -w '0x0098c9c3 5' /dev/v4l-subdev3
Device /dev/v4l-subdev3 opened.
Control 0x0098c9c3 set to 5, is 5
yavta -w '0x0098c9a1 80' /dev/v4l-subdev0 --no-query
Device /dev/v4l-subdev0 opened.
Control 0x0098c9a1 set to 80, is 80
yavta -w '0x0098c9a2 65' /dev/v4l-subdev0 --no-query
Device /dev/v4l-subdev0 opened.
Control 0x0098c9a2 set to 65, is 65
yavta -w '0x0098c9a3 35' /dev/v4l-subdev0 --no-query
Device /dev/v4l-subdev0 opened.
Control 0x0098c9a3 set to 35, is 35
yavta -w '0x0098c9a5 40' /dev/v4l-subdev0 --no-query
Device /dev/v4l-subdev0 opened.
Control 0x0098c9a5 set to 40, is 40
yavta -w '0x0098c9a4 24' /dev/v4l-subdev0 --no-query
Device /dev/v4l-subdev0 opened.
Control 0x0098c9a4 set to 24, is 24
v4l2-ctl --set-ctrl=analogue_gain=960
v4l2-ctl --set-ctrl=digital_gain=400
```

```console
shell$ sudo media-ctl -p
Media controller API version 6.1.70

Media device information
------------------------
driver          xilinx-video
model           Xilinx Video Composite Device
serial
bus info        platform:axi:vcap_v_proc_ss_sca
hw revision     0x0
driver version  6.1.70

Device topology
- entity 1: vcap_v_proc_ss_scaler output 0 (1 pad, 1 link)
            type Node subtype V4L flags 0
            device node name /dev/video0
        pad0: Sink
                <- "a0080000.v_proc_ss_scaler":1 [ENABLED]

- entity 5: a0080000.v_proc_ss_scaler (2 pads, 2 links)
            type V4L2 subdev subtype Unknown flags 0
            device node name /dev/v4l-subdev0
        pad0: Sink
                [fmt:RBG888_1X24/1536x864 field:none]
                <- "a0040000.v_proc_ss_csc":1 [ENABLED]
        pad1: Source
                [fmt:RBG888_1X24/1536x864 field:none]
                -> "vcap_v_proc_ss_scaler output 0":0 [ENABLED]

- entity 8: imx708_wide (2 pads, 1 link)
            type V4L2 subdev subtype Sensor flags 0
            device node name /dev/v4l-subdev1
        pad0: Source
                [fmt:SRGGB10_1X10/1536x864 field:none colorspace:raw xfer:none ycbcr:601 quantization:full-range
                 crop.bounds:(16,24)/4608x2592
                 crop:(784,456)/3072x1728]
                -> "80002000.mipi_csi2_rx_subsystem":0 [ENABLED]
        pad1: Source
                [fmt:unknown/28800x1 field:none
                 crop.bounds:(16,24)/4608x2592
                 crop:(784,456)/3072x1728]

- entity 11: a0040000.v_proc_ss_csc (2 pads, 2 links)
             type V4L2 subdev subtype Unknown flags 0
             device node name /dev/v4l-subdev2
        pad0: Sink
                [fmt:RBG888_1X24/1536x864 field:none]
                <- "a0030000.v_gamma_lut":1 [ENABLED]
        pad1: Source
                [fmt:RBG888_1X24/1536x864 field:none]
                -> "a0080000.v_proc_ss_scaler":0 [ENABLED]

- entity 14: a0030000.v_gamma_lut (2 pads, 2 links)
             type V4L2 subdev subtype Unknown flags 0
             device node name /dev/v4l-subdev3
        pad0: Sink
                [fmt:RBG888_1X24/1536x864 field:none]
                <- "a0010000.v_demosaic":1 [ENABLED]
        pad1: Source
                [fmt:RBG888_1X24/1536x864 field:none]
                -> "a0040000.v_proc_ss_csc":0 [ENABLED]

- entity 17: a0010000.v_demosaic (2 pads, 2 links)
             type V4L2 subdev subtype Unknown flags 0
             device node name /dev/v4l-subdev4
        pad0: Sink
                [fmt:SRGGB10_1X10/1536x864 field:none]
                <- "80002000.mipi_csi2_rx_subsystem":1 [ENABLED]
        pad1: Source
                [fmt:RBG888_1X24/1536x864 field:none]
                -> "a0030000.v_gamma_lut":0 [ENABLED]

- entity 20: 80002000.mipi_csi2_rx_subsystem (2 pads, 2 links)
             type V4L2 subdev subtype Unknown flags 0
             device node name /dev/v4l-subdev5
        pad0: Sink
                [fmt:SRGGB10_1X10/1536x864 field:none]
                <- "imx708_wide":0 [ENABLED]
        pad1: Source
                [fmt:SRGGB10_1X10/1536x864 field:none]
                -> "a0010000.v_demosaic":0 [ENABLED]
```

Capture by camera
------------------------------------------------------------------------------------

### ~~Run tools/capture_jpeg.sh~~ -> not work

<details><summary>log</summary>

```console
shell$ sudo sh tools/capture_jpeg.sh
Setting pipeline to PAUSED ...
Pipeline is live and does not need PREROLL ...
Pipeline is PREROLLED ...
Setting pipeline to PLAYING ...
0:00:00.151391157  3890   0x559994dc00 INFO                 v4l2src gstv4l2src.c:550:gst_v4l2src_query_preferred_size:<v4l2src0> Detect input 0 as `a0080000.v_proc_ss_scaler`
New clock: GstSystemClock
0:00:00.151600960  3890   0x559994dc00 WARN                    v4l2 gstv4l2object.c:4524:gst_v4l2_object_probe_caps:<v4l2src0:src> Failed to probe pixel aspect ratio with VIDIOC_CROPCAP: Invalid argument
0:00:00.152182100  3890   0x559994dc00 DEBUG                v4l2src gstv4l2src.c:601:gst_v4l2src_negotiate:<v4l2src0> caps of src: video/x-raw(format:Interlaced), format=(string)BGRx, framerate=(fraction)[ 0/1, 2147483647/1 ], width=(int)[ 1, 16383 ], height=(int)[ 1, 8191 ], interlace-mode=(string)alternate; video/x-raw, format=(string)BGRx, framerate=(fraction)[ 0/1, 2147483647/1 ], width=(int)[ 1, 16383 ], height=(int)[ 1, 8191 ], interlace-mode=(string){ progressive, interleaved }; video/x-raw(format:Interlaced), format=(string)BGRx, framerate=(fraction)[ 0/1, 2147483647/1 ], width=(int)[ 1, 16383 ], height=(int)[ 1, 8191 ], interlace-mode=(string)alternate; video/x-raw(format:Interlaced), format=(string)xBGR, framerate=(fraction)[ 0/1, 2147483647/1 ], width=(int)[ 1, 16383 ], height=(int)[ 1, 8191 ], interlace-mode=(string)alternate; video/x-raw, format=(string)xBGR, framerate=(fraction)[ 0/1, 2147483647/1 ], width=(int)[ 1, 16383 ], height=(int)[ 1, 8191 ], interlace-mode=(string){ progressive, interleaved }; video/x-raw(format:Interlaced), format=(string)xBGR, framerate=(fraction)[ 0/1, 2147483647/1 ], width=(int)[ 1, 16383 ], height=(int)[ 1, 8191 ], interlace-mode=(string)alternate; video/x-raw(format:Interlaced), format=(string)BGR, framerate=(fraction)[ 0/1, 2147483647/1 ], width=(int)[ 1, 21844 ], height=(int)[ 1, 8191 ], interlace-mode=(string)alternate; video/x-raw, format=(string)BGR, framerate=(fraction)[ 0/1, 2147483647/1 ], width=(int)[ 1, 21844 ], height=(int)[ 1, 8191 ], interlace-mode=(string){ progressive, interleaved }; video/x-raw(format:Interlaced), format=(string)BGR, framerate=(fraction)[ 0/1, 2147483647/1 ], width=(int)[ 1, 21844 ], height=(int)[ 1, 8191 ], interlace-mode=(string)alternate; video/x-raw(format:Interlaced), format=(string)RGB, framerate=(fraction)[ 0/1, 2147483647/1 ], width=(int)[ 1, 21844 ], height=(int)[ 1, 8191 ], interlace-mode=(string)alternate; video/x-raw, format=(string)RGB, framerate=(fraction)[ 0/1, 2147483647/1 ], width=(int)[ 1, 21844 ], height=(int)[ 1, 8191 ], interlace-mode=(string){ progressive, interleaved }; video/x-raw(format:Interlaced), format=(string)RGB, framerate=(fraction)[ 0/1, 2147483647/1 ], width=(int)[ 1, 21844 ], height=(int)[ 1, 8191 ], interlace-mode=(string)alternate
0:00:00.152439915  3890   0x559994dc00 DEBUG                v4l2src gstv4l2src.c:609:gst_v4l2src_negotiate:<v4l2src0> caps of peer: video/x-raw, width=(int)1536, height=(int)864, framerate=(fraction)[ 0/1, 2147483647/1 ], format=(string){ I420, YV12, YUY2, UYVY, Y41B, Y42B, YVYU, Y444, NV21, NV12, RGB, BGR, RGBx, xRGB, BGRx, xBGR, GRAY8 }
0:00:00.152615708  3890   0x559994dc00 DEBUG                v4l2src gstv4l2src.c:615:gst_v4l2src_negotiate:<v4l2src0> intersect: video/x-raw, width=(int)1536, height=(int)864, framerate=(fraction)[ 0/1, 2147483647/1 ], format=(string)BGRx, interlace-mode=(string){ progressive, interleaved }; video/x-raw, width=(int)1536, height=(int)864, framerate=(fraction)[ 0/1, 2147483647/1 ], format=(string)xBGR, interlace-mode=(string){ progressive, interleaved }; video/x-raw, width=(int)1536, height=(int)864, framerate=(fraction)[ 0/1, 2147483647/1 ], format=(string)BGR, interlace-mode=(string){ progressive, interleaved }; video/x-raw, width=(int)1536, height=(int)864, framerate=(fraction)[ 0/1, 2147483647/1 ], format=(string)RGB, interlace-mode=(string){ progressive, interleaved }
0:00:00.152779911  3890   0x559994dc00 DEBUG                v4l2src gstv4l2src.c:406:gst_v4l2src_fixate:<v4l2src0> Fixating caps video/x-raw, width=(int)1536, height=(int)864, framerate=(fraction)[ 0/1, 2147483647/1 ], format=(string)BGRx, interlace-mode=(string){ progressive, interleaved }; video/x-raw, width=(int)1536, height=(int)864, framerate=(fraction)[ 0/1, 2147483647/1 ], format=(string)xBGR, interlace-mode=(string){ progressive, interleaved }; video/x-raw, width=(int)1536, height=(int)864, framerate=(fraction)[ 0/1, 2147483647/1 ], format=(string)BGR, interlace-mode=(string){ progressive, interleaved }; video/x-raw, width=(int)1536, height=(int)864, framerate=(fraction)[ 0/1, 2147483647/1 ], format=(string)RGB, interlace-mode=(string){ progressive, interleaved }
0:00:00.152832842  3890   0x559994dc00 DEBUG                v4l2src gstv4l2src.c:407:gst_v4l2src_fixate:<v4l2src0> Preferred size 1536x864
0:00:00.153034375  3890   0x559994dc00 DEBUG                v4l2src gstv4l2src.c:430:gst_v4l2src_fixate:<v4l2src0> sorted and normalized caps video/x-raw, width=(int)1536, height=(int)864, framerate=(fraction)120/1, format=(string)BGRx, interlace-mode=(string){ progressive, interleaved }; video/x-raw, width=(int)1536, height=(int)864, framerate=(fraction)120/1, format=(string)xBGR, interlace-mode=(string){ progressive, interleaved }; video/x-raw, width=(int)1536, height=(int)864, framerate=(fraction)120/1, format=(string)BGR, interlace-mode=(string){ progressive, interleaved }; video/x-raw, width=(int)1536, height=(int)864, framerate=(fraction)120/1, format=(string)RGB, interlace-mode=(string){ progressive, interleaved }
0:00:00.153179178  3890   0x559994dc00 DEBUG                v4l2src gstv4l2src.c:488:gst_v4l2src_fixate:<v4l2src0> fixated caps video/x-raw, width=(int)1536, height=(int)864, framerate=(fraction)120/1, format=(string)BGRx, interlace-mode=(string)progressive, colorimetry=(string)sRGB
0:00:00.153224509  3890   0x559994dc00 INFO                 v4l2src gstv4l2src.c:647:gst_v4l2src_negotiate:<v4l2src0> fixated to: video/x-raw, width=(int)1536, height=(int)864, framerate=(fraction)120/1, format=(string)BGRx, interlace-mode=(string)progressive, colorimetry=(string)sRGB
/GstPipeline:pipeline0/GstV4l2Src:v4l2src0.GstPad:src: caps = video/x-raw, width=(int)1536, height=(int)864, framerate=(fraction)120/1, format=(string)BGRx, interlace-mode=(string)progressive, colorimetry=(string)sRGB
/GstPipeline:pipeline0/GstCapsFilter:capsfilter0.GstPad:src: caps = video/x-raw, width=(int)1536, height=(int)864, framerate=(fraction)120/1, format=(string)BGRx, interlace-mode=(string)progressive, colorimetry=(string)sRGB
/GstPipeline:pipeline0/GstJpegEnc:jpegenc0.GstPad:sink: caps = video/x-raw, width=(int)1536, height=(int)864, framerate=(fraction)120/1, format=(string)BGRx, interlace-mode=(string)progressive, colorimetry=(string)sRGB
/GstPipeline:pipeline0/GstCapsFilter:capsfilter0.GstPad:sink: caps = video/x-raw, width=(int)1536, height=(int)864, framerate=(fraction)120/1, format=(string)BGRx, interlace-mode=(string)progressive, colorimetry=(string)sRGB
```
</details>
```

### Run example/v4l2_capture_simple/v4l2_capture_mplane_mmap

```console
shell$ example/v4l2_capture_simple/v4l2_capture_mplane_mmap
Frame :
  Width   : 1920
  Height  : 1080
Frames    : 10
Proc Time : # Average Per Frame
  Total   : 0.115478984 #[Second]
  Wait    : 0.005619997 #[Second]
  Dequeue : 0.000007525 #[Second]
  Run     : 0.109804938 #[Second]
  Enqueue : 0.000044927 #[Second]
FPS       : 8.659584305 #[Frames Per Second]
```

### Run example/v4l2_capture_simple/v4l2_capture_mplane_dma_heap

```console
shell$ sudo example/v4l2_capture_simple/v4l2_capture_mplane_dma_heap
Frame :
  Width   : 1920
  Height  : 1080
Frames    : 10
Proc Time : # Average Per Frame
  Total   : 0.026291081 #[Second]
  Wait    : 0.005623366 #[Second]
  Dequeue : 0.000007080 #[Second]
  Run     : 0.020613501 #[Second]
  Enqueue : 0.000045406 #[Second]
FPS       : 38.035712423 #[Frames Per Second]

OpenCV example
------------------------------------------------------------------------------------

### save still
```console
shell$ cd example/still
shell$ mkdir build
shell$ cd build
shell$ cmake ..
shell$ make -j4
shell$ ./still
```

### show capture
```console
shell$ cd example/capture
shell$ mkdir build
shell$ cd build
shell$ cmake ..
shell$ make -j4
shell$ ./capture
```

Setup video4linux (HD)
------------------------------------------------------------------------------------

### Run tools/setup_hd.sh

Rewrite `v4l2_entry_imx708` in [tools/setup_hd.sh](tools/setup_hd.sh) before execution according to the specifications of the camera to be used.

|             | Normal filter | No-IR filter       |
| ----        | ----          | ----               |
| Normal lens | `imx708`      | `imx708_noir`      |
| Wide lens   | `imx708_wide` | `imx708_wide_noir` |

```console
shell$ sudo sh tools/setup_hd.sh -s -v
# mipi_csi2_rx:
#   entry  : 80002000.mipi_csi2_rx_subsystem
#   device : /dev/v4l-subdev5
# v_demosaic:
#   entry  : a0010000.v_demosaic
#   device : /dev/v4l-subdev4
# v_gamma_lut:
#   entry  : a0030000.v_gamma_lut
#   device : /dev/v4l-subdev3
# v_proc_ss_csc:
#   entry  : a0040000.v_proc_ss_csc
#   device : /dev/v4l-subdev2
# v_proc_ss_scaler:
#   entry  : a0080000.v_proc_ss_scaler
#   device : /dev/v4l-subdev0
### SONY IMX708 Sensor ###
media-ctl -d /dev/media0 --set-v4l2 '"imx708_wide":0 [fmt:SRGGB10_1X10/2304x1296]'
### MIPI CSI2-Rx ###
media-ctl -d /dev/media0 --set-v4l2 '"80002000.mipi_csi2_rx_subsystem":0 [fmt:SRGGB10_1X10/2304x1296 field:none]'
media-ctl -d /dev/media0 --set-v4l2 '"80002000.mipi_csi2_rx_subsystem":1 [fmt:SRGGB10_1X10/2304x1296 field:none]'
### Demosaic IP subdev2 ###
media-ctl -d /dev/media0 --set-v4l2 '"a0010000.v_demosaic":0 [fmt:SRGGB10_1X10/2304x1296 field:none]'
media-ctl -d /dev/media0 --set-v4l2 '"a0010000.v_demosaic":1 [fmt:RBG888_1X24/2304x1296 field:none]'
### Gamma LUT IP ###
media-ctl -d /dev/media0 --set-v4l2 '"a0030000.v_gamma_lut":0 [fmt:RBG888_1X24/2304x1296 field:none]'
media-ctl -d /dev/media0 --set-v4l2 '"a0030000.v_gamma_lut":1 [fmt:RBG888_1X24/2304x1296 field:none]'
### VPSS: Color Space Conversion (CSC) Only ###
media-ctl -d /dev/media0 --set-v4l2 '"a0040000.v_proc_ss_csc":0 [fmt:RBG888_1X24/2304x1296 field:none]'
media-ctl -d /dev/media0 --set-v4l2 '"a0040000.v_proc_ss_csc":1 [fmt:RBG888_1X24/2304x1296 field:none]'
### VPSS: Scaler Only with CSC ###
media-ctl -d /dev/media0 --set-v4l2 '"a0080000.v_proc_ss_scaler":0 [fmt:RBG888_1X24/2304x1296 field:none]'
media-ctl -d /dev/media0 --set-v4l2 '"a0080000.v_proc_ss_scaler":1 [fmt:RBG888_1X24/1920x1080 field:none]'
yavta --no-query -w '0x0098c9c1 5' /dev/v4l-subdev3
Device /dev/v4l-subdev3 opened.
Control 0x0098c9c1 set to 5, is 5
yavta --no-query -w '0x0098c9c2 5' /dev/v4l-subdev3
Device /dev/v4l-subdev3 opened.
Control 0x0098c9c2 set to 5, is 5
yavta --no-query -w '0x0098c9c3 5' /dev/v4l-subdev3
Device /dev/v4l-subdev3 opened.
Control 0x0098c9c3 set to 5, is 5
yavta -w '0x0098c9a1 80' /dev/v4l-subdev0 --no-query
Device /dev/v4l-subdev0 opened.
Control 0x0098c9a1 set to 80, is 80
yavta -w '0x0098c9a2 65' /dev/v4l-subdev0 --no-query
Device /dev/v4l-subdev0 opened.
Control 0x0098c9a2 set to 65, is 65
yavta -w '0x0098c9a3 35' /dev/v4l-subdev0 --no-query
Device /dev/v4l-subdev0 opened.
Control 0x0098c9a3 set to 35, is 35
yavta -w '0x0098c9a5 40' /dev/v4l-subdev0 --no-query
Device /dev/v4l-subdev0 opened.
Control 0x0098c9a5 set to 40, is 40
yavta -w '0x0098c9a4 24' /dev/v4l-subdev0 --no-query
Device /dev/v4l-subdev0 opened.
Control 0x0098c9a4 set to 24, is 24
v4l2-ctl --set-ctrl=analogue_gain=960
v4l2-ctl --set-ctrl=digital_gain=400
```

```console
shell$ sudo media-ctl -p
Media controller API version 6.1.70

Media device information
------------------------
driver          xilinx-video
model           Xilinx Video Composite Device
serial
bus info        platform:axi:vcap_v_proc_ss_sca
hw revision     0x0
driver version  6.1.70

Device topology
- entity 1: vcap_v_proc_ss_scaler output 0 (1 pad, 1 link)
            type Node subtype V4L flags 0
            device node name /dev/video0
        pad0: Sink
                <- "a0080000.v_proc_ss_scaler":1 [ENABLED]

- entity 5: a0080000.v_proc_ss_scaler (2 pads, 2 links)
            type V4L2 subdev subtype Unknown flags 0
            device node name /dev/v4l-subdev0
        pad0: Sink
                [fmt:RBG888_1X24/2304x1296 field:none]
                <- "a0040000.v_proc_ss_csc":1 [ENABLED]
        pad1: Source
                [fmt:RBG888_1X24/1920x1080 field:none]
                -> "vcap_v_proc_ss_scaler output 0":0 [ENABLED]

- entity 8: a0040000.v_proc_ss_csc (2 pads, 2 links)
            type V4L2 subdev subtype Unknown flags 0
            device node name /dev/v4l-subdev1
        pad0: Sink
                [fmt:RBG888_1X24/2304x1296 field:none]
                <- "a0030000.v_gamma_lut":1 [ENABLED]
        pad1: Source
                [fmt:RBG888_1X24/2304x1296 field:none]
                -> "a0080000.v_proc_ss_scaler":0 [ENABLED]

- entity 11: a0030000.v_gamma_lut (2 pads, 2 links)
             type V4L2 subdev subtype Unknown flags 0
             device node name /dev/v4l-subdev2
        pad0: Sink
                [fmt:RBG888_1X24/2304x1296 field:none]
                <- "a0010000.v_demosaic":1 [ENABLED]
        pad1: Source
                [fmt:RBG888_1X24/2304x1296 field:none]
                -> "a0040000.v_proc_ss_csc":0 [ENABLED]

- entity 14: imx708_wide (2 pads, 1 link)
             type V4L2 subdev subtype Sensor flags 0
             device node name /dev/v4l-subdev3
        pad0: Source
                [fmt:SRGGB10_1X10/2304x1296 field:none colorspace:raw xfer:none ycbcr:601 quantization:full-range
                 crop.bounds:(16,24)/4608x2592
                 crop:(16,24)/4608x2592]
                -> "80002000.mipi_csi2_rx_subsystem":0 [ENABLED]
        pad1: Source
                [fmt:unknown/28800x1 field:none
                 crop.bounds:(16,24)/4608x2592
                 crop:(16,24)/4608x2592]

- entity 17: a0010000.v_demosaic (2 pads, 2 links)
             type V4L2 subdev subtype Unknown flags 0
             device node name /dev/v4l-subdev4
        pad0: Sink
                [fmt:SRGGB10_1X10/2304x1296 field:none]
                <- "80002000.mipi_csi2_rx_subsystem":1 [ENABLED]
        pad1: Source
                [fmt:RBG888_1X24/2304x1296 field:none]
                -> "a0030000.v_gamma_lut":0 [ENABLED]

- entity 20: 80002000.mipi_csi2_rx_subsystem (2 pads, 2 links)
             type V4L2 subdev subtype Unknown flags 0
             device node name /dev/v4l-subdev5
        pad0: Sink
                [fmt:SRGGB10_1X10/2304x1296 field:none]
                <- "imx708_wide":0 [ENABLED]
        pad1: Source
                [fmt:SRGGB10_1X10/2304x1296 field:none]
                -> "a0010000.v_demosaic":0 [ENABLED]
```

OpenCV example (HD)
------------------------------------------------------------------------------------

### save still (HD)
```console
shell$ cd example/still_hd
shell$ mkdir build
shell$ cd build
shell$ cmake ..
shell$ make -j4
shell$ ./still
```

### show capture (HD)
```console
shell$ cd example/capture_hd
shell$ mkdir build
shell$ cd build
shell$ cmake ..
shell$ make -j4
shell$ ./capture
```
