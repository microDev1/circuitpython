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

#include "shared-bindings/mesh/__init__.h"

//| """MESH Module
//|
//| The `mesh` module provides necessary low-level functionality for creating
//| and managing a mesh network.
//|
//| """
//| ...
//|

// Called when mesh is imported.
STATIC mp_obj_t mesh___init__(void) {
    common_hal_mesh_init();
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(mesh___init___obj, mesh___init__);

STATIC const mp_rom_map_elem_t mesh_module_globals_table[] = {
    // module name
    { MP_ROM_QSTR(MP_QSTR___name__),    MP_ROM_QSTR(MP_QSTR_mesh) },
    // module initialixation
    { MP_ROM_QSTR(MP_QSTR___init__),    MP_ROM_PTR(&mesh___init___obj) },
    // module functions

};
STATIC MP_DEFINE_CONST_DICT(mesh_module_globals, mesh_module_globals_table);

const mp_obj_module_t mesh_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mesh_module_globals,
};
