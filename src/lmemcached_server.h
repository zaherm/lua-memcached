#ifndef LMEMCACHED_SERVER_H
#define LMEMCACHED_SERVER_H

#define LMEMCACHED_SERVER_MT "memcached.server"
#include "memcached.h"
#include "lmemcached_aux.h"

typedef struct {
  const memcached_instance_st *ptr;
} lmemcached_server;

LUALIB_API int lmemcached_server_create(lua_State *L);
LUALIB_API int lmemcached_server_free(lua_State *L);
LUALIB_API int lmemcached_server_index(lua_State *L);

LUALIB_API void lmemcached_server_open(lua_State *L);
#endif

