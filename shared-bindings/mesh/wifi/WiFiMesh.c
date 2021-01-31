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

#include "shared-bindings/mesh/wifi/WiFiMesh.h"

#include "py/objproperty.h"

//| class WiFiMesh:
//|     """Trigger an alarm when touch is detected."""
//|
//|     def __init__(self,
//|                 meshid: ReadableBuffer,
//|                 password: ReadableBuffer = b"",
//|                 *,
//|                 channel: Optional[int] = 0) -> None:
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
//|            If ``meshid`` is given, the scan will start at the first channel or the one given and
//|            connect to the mesh router with the given ``meshid`` and ``ssid``."""
//|         ...
//|
STATIC mp_obj_t mesh_wifi_wifimesh_make_new(const mp_obj_type_t *type,
        mp_uint_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    enum { ARG_meshid, ARG_password, ARG_channel, ARG_authmode, ARG_topology, ARG_max_node };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_meshid,   MP_ARG_REQUIRED | MP_ARG_OBJ },
        { MP_QSTR_password, MP_ARG_OBJ, {.u_obj = MP_OBJ_NULL} },
        { MP_QSTR_channel,  MP_ARG_KW_ONLY | MP_ARG_INT, {.u_int = 1} },
        { MP_QSTR_authmode, MP_ARG_KW_ONLY | MP_ARG_OBJ, {.u_obj = MP_OBJ_NULL} },
        { MP_QSTR_topology, MP_ARG_KW_ONLY | MP_ARG_OBJ, {.u_obj = MP_OBJ_NULL} },
        { MP_QSTR_max_node, MP_ARG_KW_ONLY | MP_ARG_INT, {.u_int = 0} },
    };

    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    #define MAC_ADDRESS_LENGTH 6

    mp_buffer_info_t meshid;
    mp_get_buffer_raise(args[ARG_meshid].u_obj, &meshid, MP_BUFFER_READ);
    if (meshid.len != MAC_ADDRESS_LENGTH) {
        mp_raise_ValueError(translate("invalid meshid"));
    }

    mp_buffer_info_t password;
    password.len = 0;
    if (args[ARG_password].u_obj != MP_OBJ_NULL) {
        mp_get_buffer_raise(args[ARG_password].u_obj, &password, MP_BUFFER_READ);
        if (password.len > 0 && (password.len < 8 || password.len > 63)) {
            mp_raise_ValueError(translate("password must be between 8 and 63 characters"));
        }
    }

    mesh_wifi_wifimesh_obj_t *self = m_new_obj(mesh_wifi_wifimesh_obj_t);
    self->base.type = &mesh_wifi_wifimesh_type;

    common_hal_mesh_wifi_wifimesh_construct(self, meshid, password, args[ARG_channel].u_int,
            args[ARG_authmode].u_obj, args[ARG_topology].u_obj, args[ARG_max_node].u_int);

    return MP_OBJ_FROM_PTR(self);
}

//|     meshid: str
//|     """String id of the mesh network"""
//|
STATIC mp_obj_t mesh_wifi_wifimesh_get_meshid(mp_obj_t self) {
    return common_hal_mesh_wifi_wifimesh_get_meshid(self);

}
MP_DEFINE_CONST_FUN_OBJ_1(mesh_wifi_wifimesh_get_meshid_obj, mesh_wifi_wifimesh_get_meshid);

const mp_obj_property_t mesh_wifi_wifimesh_meshid_obj = {
    .base.type = &mp_type_property,
    .proxy = { (mp_obj_t)&mesh_wifi_wifimesh_get_meshid_obj,
               (mp_obj_t)&mp_const_none_obj,
               (mp_obj_t)&mp_const_none_obj },
};

//|     channel: int
//|     """Channel number the mesh network is operating on"""
//|
STATIC mp_obj_t mesh_wifi_wifimesh_get_channel(mp_obj_t self) {
    return common_hal_mesh_wifi_wifimesh_get_channel(self);

}
MP_DEFINE_CONST_FUN_OBJ_1(mesh_wifi_wifimesh_get_channel_obj, mesh_wifi_wifimesh_get_channel);

const mp_obj_property_t mesh_wifi_wifimesh_channel_obj = {
    .base.type = &mp_type_property,
    .proxy = { (mp_obj_t)&mesh_wifi_wifimesh_get_channel_obj,
               (mp_obj_t)&mp_const_none_obj,
               (mp_obj_t)&mp_const_none_obj },
};

//|     authmode: str
//|     """String id of the authmode"""
//|
STATIC mp_obj_t mesh_wifi_wifimesh_get_authmode(mp_obj_t self) {
    return common_hal_mesh_wifi_wifimesh_get_authmode(self);

}
MP_DEFINE_CONST_FUN_OBJ_1(mesh_wifi_wifimesh_get_authmode_obj, mesh_wifi_wifimesh_get_authmode);

const mp_obj_property_t mesh_wifi_wifimesh_authmode_obj = {
    .base.type = &mp_type_property,
    .proxy = { (mp_obj_t)&mesh_wifi_wifimesh_get_authmode_obj,
               (mp_obj_t)&mp_const_none_obj,
               (mp_obj_t)&mp_const_none_obj },
};

STATIC const mp_rom_map_elem_t mesh_wifi_wifimesh_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_meshid),      MP_ROM_PTR(&mesh_wifi_wifimesh_meshid_obj) },
    { MP_ROM_QSTR(MP_QSTR_channel),     MP_ROM_PTR(&mesh_wifi_wifimesh_channel_obj) },
    { MP_ROM_QSTR(MP_QSTR_authmode),    MP_ROM_PTR(&mesh_wifi_wifimesh_authmode_obj) },
};
STATIC MP_DEFINE_CONST_DICT(mesh_wifi_wifimesh_locals_dict, mesh_wifi_wifimesh_locals_dict_table);

const mp_obj_type_t mesh_wifi_wifimesh_type = {
    { &mp_type_type },
    .name = MP_QSTR_WiFiMesh,
    .make_new = mesh_wifi_wifimesh_make_new,
    .locals_dict = (mp_obj_t)&mesh_wifi_wifimesh_locals_dict,
};
