/*
 * LOONGARCH LSX optimizations for libjpeg-turbo
 *
 * Copyright (C) 2023 Loongson Technology Corporation Limited
 * All rights reserved.
 * Contributed by Song Ding (songding@loongson.cn)
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#define JPEG_INTERNALS
#include "../../jinclude.h"
#include "../../jpeglib.h"
#include "../../jsimd.h"
#include "jmacros_lsx.h"

/* Y  =  0.29900 * R + 0.58700 * G + 0.11400 * B */
/* Cb = -0.16874 * R - 0.33126 * G + 0.50000 * B  + 128 */
/* Cr =  0.50000 * R - 0.41869 * G - 0.08131 * B  + 128 */
/*
0.29900 * 65536 = 19595
0.58700 * 65535 = 38470
0.11400 * 65536 = 7471
0.16874 * 65536 = 11059
0.33126 * 65536 = 21709
0.50000 * 65536 = 32768
0.41869 * 65536 = 27439
0.08131 * 65536 = 5329
*/

#define SCALEBITS 16
#define ONE_HALF 32768
#define CBCR_OFFSET (128 << SCALEBITS)
#define GETSAMPLE(_in) ((int)(_in))

#define LSX_CALC_Y(_in0, _in1, _in2, _out) {   \
  _out = __lsx_vmul_w(_in0, const1959);        \
  _out = __lsx_vmadd_w(_out, _in1, const3847); \
  _out = __lsx_vmadd_w(_out, _in2, const7471); \
}

#define LSX_CALC_CB(_in0, _in1, _in2, _out) {       \
  _out = __lsx_vmsub_w(constminu, _in0, const1105); \
  _out = __lsx_vmsub_w(_out, _in1, const2170);      \
  _out = __lsx_vmadd_w(_out, _in2, const3276);      \
}

#define LSX_CALC_CR(_in0, _in1, _in2, _out) {       \
  _out = __lsx_vmadd_w(constminu, _in0, const3276); \
  _out = __lsx_vmsub_w(_out, _in1, const2743);      \
  _out = __lsx_vmsub_w(_out, _in2, const5329);      \
}

#include "jccolext-lsx.c"
#undef RGB_RED
#undef RGB_GREEN
#undef RGB_BLUE
#undef RGB_PIXELSIZE

#define RGB_RED        EXT_RGB_RED
#define RGB_GREEN      EXT_RGB_GREEN
#define RGB_BLUE       EXT_RGB_BLUE
#define RGB_PIXELSIZE  EXT_RGB_PIXELSIZE
#define jsimd_rgb_ycc_convert_lsx  jsimd_extrgb_ycc_convert_lsx
#include "jccolext-lsx.c"
#undef RGB_RED
#undef RGB_GREEN
#undef RGB_BLUE
#undef RGB_PIXELSIZE
#undef jsimd_rgb_ycc_convert_lsx

#define RGB_RED        EXT_BGR_RED
#define RGB_GREEN      EXT_BGR_GREEN
#define RGB_BLUE       EXT_BGR_BLUE
#define RGB_PIXELSIZE  EXT_BGR_PIXELSIZE
#define jsimd_rgb_ycc_convert_lsx  jsimd_extbgr_ycc_convert_lsx
#include "jccolext-lsx.c"
#undef RGB_RED
#undef RGB_GREEN
#undef RGB_BLUE
#undef RGB_PIXELSIZE
#undef jsimd_rgb_ycc_convert_lsx

#define RGB_RED        EXT_RGBX_RED
#define RGB_GREEN      EXT_RGBX_GREEN
#define RGB_BLUE       EXT_RGBX_BLUE
#define RGB_PIXELSIZE  EXT_RGBX_PIXELSIZE
#define jsimd_rgb_ycc_convert_lsx  jsimd_extrgbx_ycc_convert_lsx
#include "jccolext-lsx.c"
#undef RGB_RED
#undef RGB_GREEN
#undef RGB_BLUE
#undef RGB_PIXELSIZE
#undef jsimd_rgb_ycc_convert_lsx

#define RGB_RED        EXT_BGRX_RED
#define RGB_GREEN      EXT_BGRX_GREEN
#define RGB_BLUE       EXT_BGRX_BLUE
#define RGB_PIXELSIZE  EXT_BGRX_PIXELSIZE
#define jsimd_rgb_ycc_convert_lsx  jsimd_extbgrx_ycc_convert_lsx
#include "jccolext-lsx.c"
#undef RGB_RED
#undef RGB_GREEN
#undef RGB_BLUE
#undef RGB_PIXELSIZE
#undef jsimd_rgb_ycc_convert_lsx

#define RGB_RED        EXT_XRGB_RED
#define RGB_GREEN      EXT_XRGB_GREEN
#define RGB_BLUE       EXT_XRGB_BLUE
#define RGB_PIXELSIZE  EXT_XRGB_PIXELSIZE
#define jsimd_rgb_ycc_convert_lsx  jsimd_extxrgb_ycc_convert_lsx
#include "jccolext-lsx.c"
#undef RGB_RED
#undef RGB_GREEN
#undef RGB_BLUE
#undef RGB_PIXELSIZE
#undef jsimd_rgb_ycc_convert_lsx

#define RGB_RED        EXT_XBGR_RED
#define RGB_GREEN      EXT_XBGR_GREEN
#define RGB_BLUE       EXT_XBGR_BLUE
#define RGB_PIXELSIZE  EXT_XBGR_PIXELSIZE
#define jsimd_rgb_ycc_convert_lsx  jsimd_extxbgr_ycc_convert_lsx
#include "jccolext-lsx.c"
#undef RGB_RED
#undef RGB_GREEN
#undef RGB_BLUE
#undef RGB_PIXELSIZE
#undef jsimd_rgb_ycc_convert_lsx