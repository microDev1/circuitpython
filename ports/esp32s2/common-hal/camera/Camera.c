/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2020 microDev
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <fcntl.h>
#include <string.h>

#include "py/runtime.h"
#include "shared-bindings/camera/Camera.h"

#include "cam.h"

typedef struct {
    uint16_t width;
    uint16_t height;
} image_size_t;

STATIC const image_size_t image_size_table[] = {
    /*{ VIDEO_HSIZE_QVGA, VIDEO_VSIZE_QVGA },
    { VIDEO_HSIZE_VGA, VIDEO_VSIZE_VGA },
    { VIDEO_HSIZE_HD, VIDEO_VSIZE_HD },
    { VIDEO_HSIZE_QUADVGA, VIDEO_VSIZE_QUADVGA },
    { VIDEO_HSIZE_FULLHD, VIDEO_VSIZE_FULLHD },
    { VIDEO_HSIZE_3M, VIDEO_VSIZE_3M },
    { VIDEO_HSIZE_5M, VIDEO_VSIZE_5M },*/
};

static bool camera_check_width_and_height(uint16_t width, uint16_t height) {
    for (int i = 0; i < MP_ARRAY_SIZE(image_size_table); i++) {
        if (image_size_table[i].width == width && image_size_table[i].height == height) {
            return true;
        }
    }
    return false;
}

static bool camera_check_buffer_length(uint16_t width, uint16_t height, camera_imageformat_t format, size_t length) {
    if (format == IMAGEFORMAT_JPG) {
        // In SPRESENSE SDK, JPEG compression quality=80 by default.
        // In such setting, the maximum actual measured size of JPEG image
        // is about width * height * 2 / 9.
        return length >= (size_t)(width * height * 2 / 9);
    } else {
        return false;
    }
}

static bool camera_check_format(camera_imageformat_t format) {
    return format == IMAGEFORMAT_JPG;
}

void common_hal_camera_construct(camera_obj_t *self) {
    mp_raise_ValueError(translate("Could not initialize Camera"));
}

void common_hal_camera_deinit(camera_obj_t *self) {
    if (common_hal_camera_deinited(self)) {
        return;
    }
}

bool common_hal_camera_deinited(camera_obj_t *self) {
    return true;
}

size_t common_hal_camera_take_picture(camera_obj_t *self, uint8_t *buffer, size_t len, uint16_t width, uint16_t height, camera_imageformat_t format) {
    if (!camera_check_width_and_height(width, height)) {
        mp_raise_ValueError(translate("Size not supported"));
    }
    if (!camera_check_buffer_length(width, height, format, len)) {
        mp_raise_ValueError(translate("Buffer is too small"));
    }
    if (!camera_check_format(format)) {
        mp_raise_ValueError(translate("Format not supported"));
    }
    return (size_t)"abcd";
}
