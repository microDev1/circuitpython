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

#include "shared-bindings/mesh/ble/BLEMesh.h"
#include "shared-bindings/board/__init__.h"

#include "py/objproperty.h"

//| class WiFiMesh:
//|     """Trigger an alarm when touch is detected."""
//|
//|     def __init__(self,
//|                 ssid: ReadableBuffer,
//|                 password: ReadableBuffer = b"",
//|                 *,
//|                 channel: Optional[int] = 0,
//|                 bssid: Optional[ReadableBuffer] = b"",
//|                 timeout: Optional[float] = None) -> None:
//|         """Connects to the given ssid. Reconnections are handled automatically once one
//|            connection succeeds.
//|
//|            By default, this will scan all channels and connect to the mesh router with the
//|            given ``ssid`` and greatest signal strength (rssi).
//|
//|            If ``channel`` is given, the scan will begin with the given channel and connect to
//|            the first mesh router with the given ``ssid``. This can speed up the connection time
//|            significantly because a full scan doesn't occur.
//|
//|            If ``bssid`` is given, the scan will start at the first channel or the one given and
//|            connect to the mesh router with the given ``bssid`` and ``ssid``."""
//|         ...
//|
STATIC mp_obj_t mesh_ble_blemesh_make_new(const mp_obj_type_t *type,
        mp_uint_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    /*
    enum { ARG_cid, ARG_vid };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_cid, MP_ARG_REQUIRED | MP_ARG_OBJ },
        { MP_QSTR_vid,  MP_ARG_OBJ, {.u_obj = MP_OBJ_NULL} },
    };

    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    mesh_ble_blemesh_obj_t *self = m_new_obj(mesh_ble_blemesh_obj_t);
    self->base.type = &mesh_ble_blemesh_type;

    common_hal_mesh_ble_blemesh_construct(self);

    return MP_OBJ_FROM_PTR(self);*/
    return mp_const_none;
}

STATIC const mp_rom_map_elem_t mesh_ble_blemesh_locals_dict_table[] = {};
STATIC MP_DEFINE_CONST_DICT(mesh_ble_blemesh_locals_dict, mesh_ble_blemesh_locals_dict_table);

const mp_obj_type_t mesh_ble_blemesh_type = {
    { &mp_type_type },
    .name = MP_QSTR_WiFiMesh,
    .make_new = mesh_ble_blemesh_make_new,
    .locals_dict = (mp_obj_t)&mesh_ble_blemesh_locals_dict,
};
