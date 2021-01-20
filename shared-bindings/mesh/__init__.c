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

#include "py/obj.h"
#include "py/reload.h"
#include "py/runtime.h"

#include "shared-bindings/mesh/__init__.h"
#include "shared-bindings/mesh/Topology.h"
#include "shared-bindings/mesh/ble/BLEMesh.h"
#include "shared-bindings/mesh/wifi/WiFiMesh.h"
#include "shared-bindings/mesh/zigbee/ZigBeeMesh.h"

//| """MESH Module
//|
//| The `mesh` module provides necessary low-level functionality for creating
//| and managing a mesh network.
//|
//| """
//| ...
//|

STATIC const mp_map_elem_t mesh_ble_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__),    MP_ROM_QSTR(MP_QSTR_ble) },
    { MP_ROM_QSTR(MP_QSTR_BLEMesh),     MP_OBJ_FROM_PTR(&mesh_ble_blemesh_type) },
};

STATIC MP_DEFINE_CONST_DICT(mesh_ble_globals, mesh_ble_globals_table);

STATIC const mp_obj_module_t mesh_ble_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mesh_ble_globals,
};

STATIC const mp_map_elem_t mesh_wifi_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__),    MP_ROM_QSTR(MP_QSTR_wifi) },
    { MP_ROM_QSTR(MP_QSTR_WiFiMesh),    MP_OBJ_FROM_PTR(&mesh_wifi_wifimesh_type) },
};

STATIC MP_DEFINE_CONST_DICT(mesh_wifi_globals, mesh_wifi_globals_table);

STATIC const mp_obj_module_t mesh_wifi_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mesh_wifi_globals,
};

STATIC const mp_map_elem_t mesh_zigbee_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__),    MP_ROM_QSTR(MP_QSTR_zigbee) },
    { MP_ROM_QSTR(MP_QSTR_ZigBeeMesh),  MP_OBJ_FROM_PTR(&mesh_zigbee_zigbeemesh_type) },
};

STATIC MP_DEFINE_CONST_DICT(mesh_zigbee_globals, mesh_zigbee_globals_table);

STATIC const mp_obj_module_t mesh_zigbee_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mesh_zigbee_globals,
};

STATIC const mp_rom_map_elem_t mesh_module_globals_table[] = {
    // module name
    { MP_ROM_QSTR(MP_QSTR___name__),    MP_ROM_QSTR(MP_QSTR_mesh) },

    // mesh network modules
    { MP_ROM_QSTR(MP_QSTR_ble),         MP_OBJ_FROM_PTR(&mesh_ble_module) },
    { MP_ROM_QSTR(MP_QSTR_wifi),        MP_OBJ_FROM_PTR(&mesh_wifi_module) },
    { MP_ROM_QSTR(MP_QSTR_zigbee),      MP_OBJ_FROM_PTR(&mesh_zigbee_module) },

    // mesh network properties
    { MP_ROM_QSTR(MP_QSTR_Topology),    MP_ROM_PTR(&mesh_topology_type) },
};
STATIC MP_DEFINE_CONST_DICT(mesh_module_globals, mesh_module_globals_table);

const mp_obj_module_t mesh_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mesh_module_globals,
};
