#ifndef LMEMCACHED_SERVER_H
#define LMEMCACHED_SERVER_H

#define LMEMCACHED_SERVER_MT "memcached.server"
#include "memcached.h"
#include "lmemcached_aux.h"

typedef struct {
  const memcached_instance_st *ptr;
} lmemcached_server;

lmemcached_server *lmemcached_server_check(lua_State *L, int index);

LUALIB_API int lmemcached_server_create(lua_State *L);
LUALIB_API int lmemcached_server_free(lua_State *L);
LUALIB_API int lmemcached_server_index(lua_State *L);
LUALIB_API int lmemcached_server_response_count(lua_State *L);
LUALIB_API int lmemcached_server_port(lua_State *L);
LUALIB_API int lmemcached_server_srcport(lua_State *L);
LUALIB_API int lmemcached_server_type(lua_State *L);
LUALIB_API int lmemcached_server_major_version(lua_State *L);
LUALIB_API int lmemcached_server_minor_version(lua_State *L);
LUALIB_API int lmemcached_server_micro_version(lua_State *L);
LUALIB_API void lmemcached_server_open(lua_State *L);
#endif

