/*
 * This file is part of the Micro Python project, http://micropython.org/
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

#include "shared-bindings/wifi/AuthMode.h"

//| class AuthMode:
//|     """auth state of wifi"""
//|
//|     def __init__(self) -> None:
//|         """Enum-like class to define the auth mode of WiFi."""
//|
//|     OPEN: AuthMode
//|     """:type wifi.AuthMode:"""
//|
//|     WEP: AuthMode
//|     """:type wifi.AuthMode:"""
//|
//|     WPA: AuthMode
//|     """:type wifi.AuthMode:"""
//|
const mp_obj_type_t wifi_authmode_type;

const wifi_authmode_obj_t wifi_authmode_open_obj = {
    { &wifi_authmode_type },
};

const wifi_authmode_obj_t wifi_authmode_wep_obj = {
    { &wifi_authmode_type },
};

const wifi_authmode_obj_t wifi_authmode_wpa_obj = {
    { &wifi_authmode_type },
};

const wifi_authmode_obj_t wifi_authmode_wpa2_obj = {
    { &wifi_authmode_type },
};

const wifi_authmode_obj_t wifi_authmode_wpa3_obj = {
    { &wifi_authmode_type },
};

const wifi_authmode_obj_t wifi_authmode_psk_obj = {
    { &wifi_authmode_type },
};

const wifi_authmode_obj_t wifi_authmode_enterprise_obj = {
    { &wifi_authmode_type },
};

STATIC const mp_rom_map_elem_t wifi_authmode_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_OPEN),        MP_ROM_PTR(&wifi_authmode_open_obj) },
    { MP_ROM_QSTR(MP_QSTR_WEP),         MP_ROM_PTR(&wifi_authmode_wep_obj) },
    { MP_ROM_QSTR(MP_QSTR_WPA),         MP_ROM_PTR(&wifi_authmode_wpa_obj) },
    { MP_ROM_QSTR(MP_QSTR_WPA2),        MP_ROM_PTR(&wifi_authmode_wpa2_obj) },
    { MP_ROM_QSTR(MP_QSTR_WPA3),        MP_ROM_PTR(&wifi_authmode_wpa3_obj) },
    { MP_ROM_QSTR(MP_QSTR_PSK),         MP_ROM_PTR(&wifi_authmode_psk_obj) },
    { MP_ROM_QSTR(MP_QSTR_ENTERPRISE),  MP_ROM_PTR(&wifi_authmode_enterprise_obj) },
};
STATIC MP_DEFINE_CONST_DICT(wifi_authmode_locals_dict, wifi_authmode_locals_dict_table);

STATIC void wifi_authmode_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    qstr authmode = MP_QSTR_OPEN;
    if (MP_OBJ_TO_PTR(self_in) == MP_ROM_PTR(&wifi_authmode_wep_obj)) {
        authmode = MP_QSTR_WEP;
    } else if (MP_OBJ_TO_PTR(self_in) ==
               MP_ROM_PTR(&wifi_authmode_wpa_obj)) {
        authmode = MP_QSTR_WPA;
    } else if (MP_OBJ_TO_PTR(self_in) ==
               MP_ROM_PTR(&wifi_authmode_wpa2_obj)) {
        authmode = MP_QSTR_WPA2;
    } else if (MP_OBJ_TO_PTR(self_in) ==
               MP_ROM_PTR(&wifi_authmode_wpa3_obj)) {
        authmode = MP_QSTR_WPA3;
    } else if (MP_OBJ_TO_PTR(self_in) ==
               MP_ROM_PTR(&wifi_authmode_psk_obj)) {
        authmode = MP_QSTR_PSK;
    } else if (MP_OBJ_TO_PTR(self_in) ==
               MP_ROM_PTR(&wifi_authmode_enterprise_obj)) {
        authmode = MP_QSTR_ENTERPRISE;
    }
    mp_printf(print, "%q.%q.%q", MP_QSTR_wifi, MP_QSTR_AuthMode,
              authmode);
}

const mp_obj_type_t wifi_authmode_type = {
    { &mp_type_type },
    .name = MP_QSTR_AuthMode,
    .print = wifi_authmode_print,
    .locals_dict = (mp_obj_t)&wifi_authmode_locals_dict,
};
