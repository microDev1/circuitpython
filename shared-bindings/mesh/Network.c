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

#include "shared-bindings/mesh/Network.h"

#include <string.h>

#include "py/runtime.h"
#include "py/objproperty.h"

//| class Network:
//|     """A mesh network provided by a nearby access point.
//|
//|     """
//|

//|     def __init__(self) -> None:
//|         """You cannot create an instance of `mesh.Network`. They are returned by `mesh.Radio.start_scanning_networks`."""
//|         ...
//|

//|     ssid: str
//|     """String id of the network"""
//|
STATIC mp_obj_t mesh_network_get_ssid(mp_obj_t self) {
    return common_hal_mesh_network_get_ssid(self);

}
MP_DEFINE_CONST_FUN_OBJ_1(mesh_network_get_ssid_obj, mesh_network_get_ssid);

const mp_obj_property_t mesh_network_ssid_obj = {
    .base.type = &mp_type_property,
    .proxy = { (mp_obj_t)&mesh_network_get_ssid_obj,
               (mp_obj_t)&mp_const_none_obj,
               (mp_obj_t)&mp_const_none_obj },
};


//|     bssid: bytes
//|     """BSSID of the network (usually the AP's MAC address)"""
//|
STATIC mp_obj_t mesh_network_get_bssid(mp_obj_t self) {
    return common_hal_mesh_network_get_bssid(self);

}
MP_DEFINE_CONST_FUN_OBJ_1(mesh_network_get_bssid_obj, mesh_network_get_bssid);

const mp_obj_property_t mesh_network_bssid_obj = {
    .base.type = &mp_type_property,
    .proxy = { (mp_obj_t)&mesh_network_get_bssid_obj,
               (mp_obj_t)&mp_const_none_obj,
               (mp_obj_t)&mp_const_none_obj },
};

/*
//|     rssi: int
//|     """Signal strength of the network"""
//|
STATIC mp_obj_t mesh_network_get_rssi(mp_obj_t self) {
    return common_hal_mesh_network_get_rssi(self);

}
MP_DEFINE_CONST_FUN_OBJ_1(mesh_network_get_rssi_obj, mesh_network_get_rssi);

const mp_obj_property_t mesh_network_rssi_obj = {
    .base.type = &mp_type_property,
    .proxy = { (mp_obj_t)&mesh_network_get_rssi_obj,
               (mp_obj_t)&mp_const_none_obj,
               (mp_obj_t)&mp_const_none_obj },
};
*/

//|     channel: int
//|     """Channel number the network is operating on"""
//|
STATIC mp_obj_t mesh_network_get_channel(mp_obj_t self) {
    return common_hal_mesh_network_get_channel(self);

}
MP_DEFINE_CONST_FUN_OBJ_1(mesh_network_get_channel_obj, mesh_network_get_channel);

const mp_obj_property_t mesh_network_channel_obj = {
    .base.type = &mp_type_property,
    .proxy = { (mp_obj_t)&mesh_network_get_channel_obj,
               (mp_obj_t)&mp_const_none_obj,
               (mp_obj_t)&mp_const_none_obj },
};

//|     authmode: str
//|     """String id of the authmode"""
//|
STATIC mp_obj_t mesh_network_get_authmode(mp_obj_t self) {
    return common_hal_mesh_network_get_authmode(self);

}
MP_DEFINE_CONST_FUN_OBJ_1(mesh_network_get_authmode_obj, mesh_network_get_authmode);

const mp_obj_property_t mesh_network_authmode_obj = {
    .base.type = &mp_type_property,
    .proxy = { (mp_obj_t)&mesh_network_get_authmode_obj,
               (mp_obj_t)&mp_const_none_obj,
               (mp_obj_t)&mp_const_none_obj },
};

STATIC const mp_rom_map_elem_t mesh_network_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_ssid), MP_ROM_PTR(&mesh_network_ssid_obj) },
    { MP_ROM_QSTR(MP_QSTR_bssid), MP_ROM_PTR(&mesh_network_bssid_obj) },
    //{ MP_ROM_QSTR(MP_QSTR_rssi), MP_ROM_PTR(&mesh_network_rssi_obj) },
    { MP_ROM_QSTR(MP_QSTR_channel), MP_ROM_PTR(&mesh_network_channel_obj) },
    { MP_ROM_QSTR(MP_QSTR_authmode), MP_ROM_PTR(&mesh_network_authmode_obj) },
};

STATIC MP_DEFINE_CONST_DICT(mesh_network_locals_dict, mesh_network_locals_dict_table);

const mp_obj_type_t mesh_network_type = {
    .base = { &mp_type_type },
    .name = MP_QSTR_Network,
    .locals_dict = (mp_obj_t)&mesh_network_locals_dict,
};
