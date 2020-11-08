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

#ifndef MICROPY_INCLUDED_ESP32S2_PERIPHERALS_CAM_H
#define MICROPY_INCLUDED_ESP32S2_PERIPHERALS_CAM_H

#include "esp_err.h"

typedef struct {
    uint8_t bit_width;
    uint32_t xclk_fre;
    union {
        struct {
            uint32_t xclk:   8;
            uint32_t pclk:   8;
            uint32_t vsync:  8;
            uint32_t hsync:  8;
        };
        uint32_t val;
    } pin;                    /*!< Pin of camera */
    uint8_t pin_data[16];     /*!< Data pin of camera*/
    uint8_t vsync_invert;
    uint8_t hsync_invert;
    union {
        struct {
            uint32_t width:   16;
            uint32_t high:    16;
        };
        uint32_t val;
    } size;                   /*!< size of camera  */
    uint32_t max_buffer_size; /*!< DMA used */
    uint32_t task_stack;      /*!< The priority of the task at run time */
    uint8_t task_pri;
    union {
        struct {
            uint32_t jpeg:   1;
        };
        uint32_t val;
    } mode;
    uint8_t *frame1_buffer; /*!< PingPang buffers , cache the image*/
    uint8_t *frame2_buffer; /*!< PingPang buffers , cache the image*/
} cam_config_t;

/**
 * @brief enable camera
 */
void cam_start(void);

/**
 * @brief disable camera
 */
void cam_stop(void);

/**
 * @brief Accepts frame data and returns a pointer to the frame data.
 *
 * @param buffer_p  The address of the frame buffer pointer
 *
 * @return - len of buffer
 */
size_t cam_take(uint8_t **buffer_p);

/**
 * @brief enable frame buffer to get the next frame data.
 *
 * @param buffer The address of the frame buffer pointer
 *
 */
void cam_give(uint8_t *buffer);

/**
 * @brief Initialize camera
 *
 * @param config Parameter configuration, including pin, buffer, output image size, and so on.
 *
 * @return - ESP_OK :Initialize success
 *           ESP_FAIL: Initialize fails
 */
esp_err_t cam_init(const cam_config_t *config);

/**
 * @brief  delete the camera
 *
 * @return - ESP_OK :Delete success
 *           ESP_FAIL: Delete fails
 */
esp_err_t cam_deinit(void);

#endif  // MICROPY_INCLUDED_ESP32S2_PERIPHERALS_CAM_H
