#include "lmemcached_server.h"

lmemcached_server *lmemcached_server_check(lua_State *L, int index) {
  lmemcached_server *s = (lmemcached_server *) luaL_checkudata(L, index, LMEMCACHED_SERVER_MT);
  luaL_argcheck(L, s != NULL && s->ptr != NULL, index, LMEMCACHED_SERVER_MT" expected");
  return s;
}

LUALIB_API int lmemcached_server_index(lua_State *L) {
  const char* key = luaL_checkstring(L, 2);
  lua_getmetatable(L, 1);
  lua_getfield(L, -1, key);
  /* return if the key present in the metatable */
  if(!lua_isnil(L, -1)) {
    return 1;
  }
  return 0;
}


LUALIB_API int lmemcached_server_response_count(lua_State *L) {
  lmemcached_server *self = lmemcached_server_check(L, 1);
  uint32_t response_count = memcached_server_response_count(self->ptr);
  lua_pushinteger(L, response_count);
  return 1;
}

LUALIB_API int lmemcached_server_port(lua_State *L) {
  lmemcached_server *self = lmemcached_server_check(L, 1);
  in_port_t port = memcached_server_port(self->ptr);
  lua_pushinteger(L, port);
  return 1;
}

LUALIB_API int lmemcached_server_srcport(lua_State *L) {
  lmemcached_server *self = lmemcached_server_check(L, 1);
  in_port_t port = memcached_server_srcport(self->ptr);
  lua_pushinteger(L, port);
  return 1;
}

LUALIB_API int lmemcached_server_type(lua_State *L) {
  lmemcached_server *self = lmemcached_server_check(L, 1);
  const char *type = memcached_server_type(self->ptr);
  lua_pushstring(L, type);
  return 1;
}

LUALIB_API int lmemcached_server_major_version(lua_State *L) {
  lmemcached_server *self = lmemcached_server_check(L, 1);
  uint8_t version = memcached_server_major_version(self->ptr);
  lua_pushinteger(L, version);
  return 1;
}


LUALIB_API int lmemcached_server_minor_version(lua_State *L) {
  lmemcached_server *self = lmemcached_server_check(L, 1);
  uint8_t version = memcached_server_minor_version(self->ptr);
  lua_pushinteger(L, version);
  return 1;
}

LUALIB_API int lmemcached_server_micro_version(lua_State *L) {
  lmemcached_server *self = lmemcached_server_check(L, 1);
  uint8_t version = memcached_server_micro_version(self->ptr);
  lua_pushinteger(L, version);
  return 1;
}


static luaL_Reg lmemcached_server_methods[] = {
  { "response_count", lmemcached_server_response_count },
  { "major_version", lmemcached_server_major_version },
  { "minor_version", lmemcached_server_minor_version },
  { "micro_version", lmemcached_server_micro_version },
  { "type", lmemcached_server_type },
  { "port", lmemcached_server_port },
  { "srcport", lmemcached_server_srcport },
  { "__index", lmemcached_server_index },
  { NULL, NULL },
};

LUALIB_API void lmemcached_server_open(lua_State *L) {
  lmemcached_createmeta(L, LMEMCACHED_SERVER_MT, lmemcached_server_methods);
}

