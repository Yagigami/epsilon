#include "modpersonal.h"

STATIC MP_DEFINE_CONST_FUN_OBJ_0(modpersonal_hello_world_obj, modpersonal_hello_world);
STATIC MP_DEFINE_CONST_FUN_OBJ_0(modpersonal_mesh_obj, modpersonal_mesh);

STATIC const mp_rom_map_elem_t modpersonal_module_globals_table[] = {
  { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_personal) },
  { MP_ROM_QSTR(MP_QSTR_hello_world), (mp_obj_t)&modpersonal_hello_world_obj },
  { MP_ROM_QSTR(MP_QSTR_mesh),        (mp_obj_t)&modpersonal_mesh_obj },
};

STATIC MP_DEFINE_CONST_DICT(modpersonal_module_globals, modpersonal_module_globals_table);

const mp_obj_module_t modpersonal_module = {
  .base = { &mp_type_module },
  .globals = (mp_obj_dict_t*)&modpersonal_module_globals,
};
