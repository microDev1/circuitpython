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

#include "shared-bindings/mesh/Topology.h"

//| class Topology:
//|     """run state of the mesh"""
//|
//|     def __init__(self) -> None:
//|         """Enum-like class to define the run mode of the mesh and
//|         CircuitPython."""
//|
//|     STAR: Topology
//|     """Run CircuitPython as star.
//|
//|     :type mesh.Topology:"""
//|
//|     TREE: Topology
//|     """Run CircuitPython in safe mode. User code will not be run and the
//|     file system will be writeable over USB.
//|
//|     :type mesh.Topology:"""
//|
//|     CHAIN: Topology
//|     """Run the chain.
//|
//|     :type mesh.Topology:"""
//|
const mp_obj_type_t mesh_topology_type;

const mesh_topology_obj_t mesh_topology_star_obj = {
    { &mesh_topology_type },
};

const mesh_topology_obj_t mesh_topology_tree_obj = {
    { &mesh_topology_type },
};

const mesh_topology_obj_t mesh_topology_chain_obj = {
    { &mesh_topology_type },
};

STATIC const mp_rom_map_elem_t mesh_topology_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_STAR),     MP_ROM_PTR(&mesh_topology_star_obj) },
    { MP_ROM_QSTR(MP_QSTR_TREE),     MP_ROM_PTR(&mesh_topology_tree_obj) },
    { MP_ROM_QSTR(MP_QSTR_CHAIN),    MP_ROM_PTR(&mesh_topology_chain_obj) },
};
STATIC MP_DEFINE_CONST_DICT(mesh_topology_locals_dict, mesh_topology_locals_dict_table);

STATIC void mesh_topology_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    qstr topology = MP_QSTR_STAR;
    if (MP_OBJ_TO_PTR(self_in) == MP_ROM_PTR(&mesh_topology_tree_obj)) {
        topology = MP_QSTR_TREE;
    } else if (MP_OBJ_TO_PTR(self_in) ==
               MP_ROM_PTR(&mesh_topology_chain_obj)) {
        topology = MP_QSTR_CHAIN;
    }
    mp_printf(print, "%q.%q.%q", MP_QSTR_mesh, MP_QSTR_Topology,
              topology);
}

const mp_obj_type_t mesh_topology_type = {
    { &mp_type_type },
    .name = MP_QSTR_Topology,
    .print = mesh_topology_print,
    .locals_dict = (mp_obj_t)&mesh_topology_locals_dict,
};
