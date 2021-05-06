/*
 * This file is part of the Micro Python project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2021 microDev
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

#include "py/stream.h"
#include "py/runtime.h"
#include "shared-bindings/traceback/__init__.h"

#if MICROPY_PY_IO
extern struct _mp_dummy_t mp_sys_stdout_obj; // type is irrelevant, just need pointer
#endif

//| """Tracback Module
//|
//| This module provides a standard interface to extract, format and print
//| stack traces of programs.
//|
//| """
//| ...
//|

//| def print_exception(exc: exceptions.Exception, file: Optional[io.StringIO]) -> None:
//|     """Print exception with a traceback to a file-like object *file*
//|        (or `sys.stdout` by default).
//|     """
//|     ...
//|
STATIC mp_obj_t traceback_print_exception(size_t n_args, const mp_obj_t *args) {
    #if MICROPY_PY_IO && MICROPY_PY_SYS_STDFILES
    void *stream_obj = &mp_sys_stdout_obj;
    if (n_args > 1) {
        mp_get_stream_raise(args[1], MP_STREAM_OP_WRITE);
        stream_obj = MP_OBJ_TO_PTR(args[1]);
    }
    mp_print_t print = {stream_obj, mp_stream_write_adaptor};
    mp_obj_print_exception(&print, args[0]);
    #else
    (void)n_args;
    mp_obj_print_exception(&mp_plat_print, args[0]);
    #endif
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(traceback_print_exception_obj, 1, 2, traceback_print_exception);

STATIC const mp_rom_map_elem_t traceback_module_globals_table[] = {
    // module name
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_traceback) },
    // module functions
    { MP_ROM_QSTR(MP_QSTR_print_exception), MP_ROM_PTR(&traceback_print_exception_obj) },
};
STATIC MP_DEFINE_CONST_DICT(traceback_module_globals, traceback_module_globals_table);

const mp_obj_module_t traceback_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&traceback_module_globals,
};
