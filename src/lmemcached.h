#ifndef LMEMCACHED_H
#define LMEMCACHED_H

#include "lauxlib.h"
#include "lua.h"
#include "memcached.h"
#include "lmemcached_aux.h"
#include "lmemcached_consts.h"
#include "lmemcached_result.h"

#define LMEMCACHED_VERSION "lua-memcached 0.0.1"
#define LMEMCACHED_COPYRIGHT "Copyright (c) 2017, Zaher Marzuq"
#define LMEMCACHED_DESCRIPTION "Lua binding for memcached"
#define LMEMCACHED_MT "memcached"

/* functions for memcached_st */
typedef struct {
  memcached_st *ptr;
} lmemcached;

LUALIB_API int lmemcached_new(lua_State *L);
LUALIB_API int lmemcached_create(lua_State *L);
LUALIB_API int lmemcached_free(lua_State *L);
LUALIB_API int lmemcached_clone(lua_State *L);
LUALIB_API int lmemcached_servers_reset(lua_State *L);
LUALIB_API int lmemcached_index(lua_State *L);
LUALIB_API int lmemcached_last_error_message(lua_State *L);
LUALIB_API int lmemcached_strerror(lua_State *L);
LUALIB_API int lmemcached_increment(lua_State *L);
LUALIB_API int lmemcached_decrement(lua_State *L);
LUALIB_API int lmemcached_increment_by_key(lua_State *L);
LUALIB_API int lmemcached_decrement_by_key(lua_State *L);
LUALIB_API int lmemcached_delete(lua_State *L);
LUALIB_API int lmemcached_delete_by_key(lua_State *L);
LUALIB_API int lmemcached_exist(lua_State *L);
LUALIB_API int lmemcached_exist_by_key(lua_State *L);
LUALIB_API int lmemcached_flush_buffers(lua_State *L);
LUALIB_API int lmemcached_flush(lua_State *L);
/* get */
LUALIB_API int lmemcached_get(lua_State *L);
LUALIB_API int lmemcached_get_by_key(lua_State *L);
LUALIB_API int lmemcached_mget(lua_State *L);
LUALIB_API int lmemcached_mget_by_key(lua_State *L);
LUALIB_API int lmemcached_fetch_result(lua_State *L);
/* set */
LUALIB_API int lmemcached_set(lua_State *L);
LUALIB_API int lmemcached_set_by_key(lua_State *L);
LUALIB_API int lmemcached_add(lua_State *L);
LUALIB_API int lmemcached_add_by_key(lua_State *L);
LUALIB_API int lmemcached_replace(lua_State *L);
LUALIB_API int lmemcached_replace_by_key(lua_State *L);
/* prepend/append */
LUALIB_API int lmemcached_prepend(lua_State *L);
LUALIB_API int lmemcached_prepend_by_key(lua_State *L);
LUALIB_API int lmemcached_append(lua_State *L);
LUALIB_API int lmemcached_append_by_key(lua_State *L);
/* cas */
LUALIB_API int lmemcached_cas(lua_State *L);
LUALIB_API int lmemcached_cas_by_key(lua_State *L);
/* encryption */
LUALIB_API int lmemcached_set_encoding_key(lua_State *L);
/* quit */
LUALIB_API int lmemcached_quit(lua_State *L);
/* behavior */
LUALIB_API int lmemcached_behavior_get(lua_State *L);
LUALIB_API int lmemcached_behavior_set(lua_State *L);

/* general */
LUALIB_API int lmemcached_lib_version(lua_State *L);
LUALIB_API int lmemcached_check_configuration(lua_State *L);

static const luaL_Reg lmemcached_funcs[] = {
  { "new", lmemcached_new },
  { "create", lmemcached_create },
  { "lib_version", lmemcached_lib_version },
  { "check_configuration", lmemcached_check_configuration },
  { NULL, NULL }
};

static luaL_Reg lmemcached_methods[] = {
  { "strerror", lmemcached_strerror },
  { "clone", lmemcached_clone },
  { "servers_reset", lmemcached_servers_reset },
  { "last_error_message", lmemcached_last_error_message },
  { "increment", lmemcached_increment },
  { "decrement", lmemcached_decrement },
  { "increment_by_key", lmemcached_increment_by_key },
  { "decrement_by_key", lmemcached_decrement_by_key },
  { "delete", lmemcached_delete },
  { "delete_by_key", lmemcached_delete_by_key },
  { "exist", lmemcached_exist },
  { "exist_by_key", lmemcached_exist_by_key },
  { "flush_buffers", lmemcached_flush_buffers },
  { "flush", lmemcached_flush },
  { "get", lmemcached_get },
  { "get_by_key", lmemcached_get_by_key },
  { "mget", lmemcached_mget },
  { "mget_by_key", lmemcached_mget_by_key },
  { "fetch_result", lmemcached_fetch_result },
  { "set", lmemcached_set },
  { "set_by_key", lmemcached_set_by_key },
  { "add", lmemcached_add },
  { "add_by_key", lmemcached_add_by_key },
  { "replace", lmemcached_replace },
  { "replace_by_key", lmemcached_replace_by_key },
  { "prepend", lmemcached_prepend },
  { "prepend_by_key", lmemcached_prepend_by_key },
  { "append", lmemcached_append },
  { "append_by_key", lmemcached_append_by_key },
  { "cas", lmemcached_cas },
  { "cas_by_key", lmemcached_cas_by_key },
  { "set_encoding_key", lmemcached_set_encoding_key },
  { "quit", lmemcached_quit },
  { "behavior_get", lmemcached_behavior_get },
  { "behavior_set", lmemcached_behavior_set },
  { "__gc", lmemcached_free },
  { "__index", lmemcached_index },
  { NULL, NULL }
};

#endif

