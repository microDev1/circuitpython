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

#include "peripherals/i2c.h"

typedef enum {
    STATUS_FREE = 0,
    STATUS_IN_USE,
    STATUS_NEVER_RESET
} i2c_status_t;

static i2c_status_t i2c_status[I2C_NUM_MAX];

void i2c_reset(void) {
    for (i2c_port_t num = 0; num < I2C_NUM_MAX; num++) {
        if (i2c_status[num] == STATUS_IN_USE) {
            i2c_driver_delete(num);
            i2c_status[num] = STATUS_FREE;
        }
    }
}

void never_reset_i2c(i2c_port_t num) {
    i2c_status[num] = STATUS_NEVER_RESET;
}

bool peripherals_i2c_init(i2c_port_t num, const i2c_config_t * i2c_conf) {
    i2c_param_config(num, i2c_conf);
    return i2c_driver_install(num, i2c_conf->mode, 0, 0, 0) == ESP_OK;
}

void peripherals_i2c_deinit(i2c_port_t num) {
    i2c_driver_delete(num);
    i2c_status[num] = STATUS_FREE;
}

i2c_port_t i2c_num_status(void) {
    i2c_port_t i2c_num = I2C_NUM_MAX;
    for (i2c_port_t num = 0; num < I2C_NUM_MAX; num++) {
        if (i2c_status[num] == STATUS_FREE) {
            i2c_num = num;
        }
    }
    if (i2c_num != I2C_NUM_MAX) {
        i2c_status[i2c_num] = STATUS_IN_USE;
    }
    return i2c_num;
}
