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

#ifndef MICROPY_INCLUDED_SHARED_BINDINGS_MESH_WIFI_WIFIMESH_H
#define MICROPY_INCLUDED_SHARED_BINDINGS_MESH_WIFI_WIFIMESH_H

#include "py/obj.h"
#include "py/runtime.h"

#include "common-hal/mesh/wifi/WiFiMesh.h"

extern const mp_obj_type_t mesh_wifi_wifimesh_type;

// object constructor
extern void common_hal_mesh_wifi_wifimesh_construct(mesh_wifi_wifimesh_obj_t *self,
    const mp_buffer_info_t meshid, const mp_buffer_info_t password, const uint8_t channel,
    const mp_obj_t authmode_obj, const mp_obj_t topology_obj, const uint16_t node, const uint8_t connection);

// mesh network config parameters
extern mp_obj_t common_hal_mesh_wifi_wifimesh_get_meshid(mesh_wifi_wifimesh_obj_t *self);
extern mp_obj_t common_hal_mesh_wifi_wifimesh_get_channel(mesh_wifi_wifimesh_obj_t *self);
extern mp_obj_t common_hal_mesh_wifi_wifimesh_get_authmode(mesh_wifi_wifimesh_obj_t *self);
extern mp_obj_t common_hal_mesh_wifi_wifimesh_get_topology(mesh_wifi_wifimesh_obj_t *self);
extern mp_obj_t common_hal_mesh_wifi_wifimesh_get_connection(mesh_wifi_wifimesh_obj_t *self);
extern mp_obj_t common_hal_mesh_wifi_wifimesh_get_node(mesh_wifi_wifimesh_obj_t *self);


#endif  // MICROPY_INCLUDED_SHARED_BINDINGS_MESH_WIFI_WIFIMESH_H
