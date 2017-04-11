#ifndef LMEMCACHED_AUX_H
#define LMEMCACHED_AUX_H
#include <string.h>
#include "lauxlib.h"

#if !defined LUA_VERSION_NUM || LUA_VERSION_NUM==501
LUALIB_API void luaL_setfuncs(lua_State *L, const luaL_Reg *l, int nup);
#endif

void lmemcached_setmeta(lua_State *L, const char *name);
void lmemcached_createmeta(lua_State *L, const char *name, const luaL_Reg *methods);
void lmemcached_error(lua_State *L, const char *msg);
void lmemcached_assert(lua_State *L, int cond, const char *msg);

#endif