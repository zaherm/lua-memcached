#ifndef LMEMCACHED_RESULT_H
#define LMEMCACHED_RESULT_H

#define LMEMCACHED_RESULT_MT "memcached.result"
#include "memcached.h"
#include "lmemcached_aux.h"

typedef struct {
  memcached_result_st *ptr;
} lmemcached_result;

LUALIB_API int lmemcached_result_create(lua_State *L);
LUALIB_API int lmemcached_result_free(lua_State *L);
LUALIB_API int lmemcached_result_index(lua_State *L);
LUALIB_API int lmemcached_result_key(lua_State *L);
LUALIB_API int lmemcached_result_value(lua_State *L);
LUALIB_API int lmemcached_result_flags(lua_State *L);
LUALIB_API int lmemcached_result_cas(lua_State *L);
LUALIB_API int lmemcached_result_set_value(lua_State *L);
LUALIB_API int lmemcached_result_set_flags(lua_State *L);
LUALIB_API int lmemcached_result_set_expiration(lua_State *L);

LUALIB_API void lmemcached_result_open(lua_State *L);
#endif

