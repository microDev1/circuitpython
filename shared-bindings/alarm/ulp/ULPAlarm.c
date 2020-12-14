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

#include "py/nlr.h"
#include "py/obj.h"
#include "py/objproperty.h"
#include "py/runtime.h"

#include "shared-bindings/alarm/ulp/ULPAlarm.h"

//| class ULPAlarm:
//|     """Trigger an alarm when the ulp co-processor requests wake-up."""
//|
//|     def __init__(self, *buffer: ReadableBuffer) -> None:
//|         """Create an alarm that will be triggered when ulp co-processor requests
//|         wake-up when certain condition (decided by ulp program) is met.
//|
//|         """
//|         ...
//|
STATIC mp_obj_t alarm_ulp_ulp_alarm_make_new(const mp_obj_type_t *type,
        mp_uint_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    alarm_ulp_ulp_alarm_obj_t *self = m_new_obj(alarm_ulp_ulp_alarm_obj_t);
    self->base.type = &alarm_ulp_ulp_alarm_type;

    enum { ARG_buffer };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_buffer, MP_ARG_REQUIRED | MP_ARG_OBJ },
    };

    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[ARG_buffer].u_obj, &bufinfo, MP_BUFFER_READ);

    common_hal_alarm_ulp_ulp_alarm_construct(self, bufinfo.buf, bufinfo.len);

    return MP_OBJ_FROM_PTR(self);
}

const mp_obj_type_t alarm_ulp_ulp_alarm_type = {
    { &mp_type_type },
    .name = MP_QSTR_ULPAlarm,
    .make_new = alarm_ulp_ulp_alarm_make_new,
};
