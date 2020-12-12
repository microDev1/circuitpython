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

#include "shared-bindings/alarm/ulp/ULPAlarm.h"

#include "py/runtime.h"

#include "esp_sleep.h"
#include "esp32s2/ulp_riscv.h"

void common_hal_alarm_ulp_ulp_alarm_construct(alarm_ulp_ulp_alarm_obj_t *self,
        const uint8_t *buf, const size_t len) {
    if (ulp_riscv_load_binary(buf, len) != ESP_OK) {
            mp_raise_RuntimeError(translate("program exceeds reserved memeory"));
    }
}

mp_obj_t alarm_ulp_ulpalarm_get_wakeup_alarm(size_t n_alarms, const mp_obj_t *alarms) {
    // First, check to see if we match
    for (size_t i = 0; i < n_alarms; i++) {
        if (MP_OBJ_IS_TYPE(alarms[i], &alarm_ulp_ulp_alarm_type)) {
            return alarms[i];
        }
    }
    alarm_ulp_ulp_alarm_obj_t *alarm = m_new_obj(alarm_ulp_ulp_alarm_obj_t);
    alarm->base.type = &alarm_ulp_ulp_alarm_type;
    return alarm;
}

void alarm_ulp_ulpalarm_set_alarm(alarm_ulp_ulp_alarm_obj_t *self) {
    esp_sleep_enable_ulp_wakeup();
    ulp_riscv_run();
}
