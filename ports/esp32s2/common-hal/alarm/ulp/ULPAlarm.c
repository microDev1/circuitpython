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

#include "esp_sleep.h"

#include "py/runtime.h"
#include "supervisor/esp_port.h"

#include "shared-bindings/alarm/ulp/ULPAlarm.h"

void common_hal_alarm_ulp_ulp_alarm_construct(alarm_ulp_ulp_alarm_obj_t *self, const uint8_t *buf, const size_t len) {
    ulp_load_binary(0, buf, len);
}

mp_obj_t alarm_ulp_ulpalarm_get_wakeup_alarm(size_t n_alarms, const mp_obj_t *alarms) {
    return mp_const_none;
}

bool alarm_ulp_ulpalarm_woke_us_up(void) {
    return false;
}

void alarm_ulp_ulpalarm_reset(void) {

}

void alarm_ulp_ulpalarm_set_alarm(alarm_ulp_ulp_alarm_obj_t *self) {

}
