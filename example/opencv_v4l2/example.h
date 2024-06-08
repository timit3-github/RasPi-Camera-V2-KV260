/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * (c) 2024 timit
 */
#include "v4ldevice.h"

#define FPS_CHECK   //フレームレート計算を行う場合は定義
#define FPS_FRAMES 30   //平均フレームレートを計測するのに使用するフレーム数
#define ENABLE_FULLSCREEN    // 全画面表示する場合は定義
#define OSD_TIMER_FRAMES  120    //OSD表示時間(フレーム数)
#define WINDOW_NAME "IMX708"
#define OSD_COLOR Scalar(0, 0, 255) // BGR

#define ADDTEXT(img, str, pt, name, size, color) \
        putText(img, str, pt, FONT_HERSHEY_COMPLEX, 1, color, 1, LINE_AA)

using namespace cv;
using namespace std;
