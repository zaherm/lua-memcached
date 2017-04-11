#include "lmemcached_result.h"

lmemcached_result *lmemcached_result_check(lua_State *L, int index) {
  lmemcached_result *r = (lmemcached_result *) luaL_checkudata(L, index, LMEMCACHED_RESULT_MT);
  luaL_argcheck(L, r != NULL && r->ptr != NULL, index, LMEMCACHED_RESULT_MT" expected");
  return r;
}

LUALIB_API int lmemcached_result_index(lua_State *L) {
  const char* key = luaL_checkstring(L, 2);
  lua_getmetatable(L, 1);
  lua_getfield(L, -1, key);
  /* return if the key present in the metatable */
  if(!lua_isnil(L, -1)) {
    return 1;
  }
  return 0;
}

LUALIB_API int lmemcached_result_free(lua_State *L) {
  lmemcached_result *self = lmemcached_result_check(L, 1);
  if(self->ptr != NULL) {
    memcached_result_free(self->ptr);
    self->ptr = NULL;
  }
  return 0;
}

/***
 * @function result:key()
 * @desc Get the key value of the result
 * @return key[string]
 * @ref http://docs.libmemcached.org/memcached_result_st.html
*/
LUALIB_API int lmemcached_result_key(lua_State *L) {
  lmemcached_result *self = lmemcached_result_check(L, 1);
  size_t length = memcached_result_key_length(self->ptr);
  const char *key = memcached_result_key_value(self->ptr);
  lua_pushlstring(L, key, length);
  return 1;
}

/***
 * @function result:value()
 * @desc Get the value
 * @return value[string]
 * @ref http://docs.libmemcached.org/memcached_result_st.html
*/
LUALIB_API int lmemcached_result_value(lua_State *L) {
  lmemcached_result *self = lmemcached_result_check(L, 1);
  size_t length = memcached_result_length(self->ptr);
  const char *value = memcached_result_value(self->ptr);
  lua_pushlstring(L, value, length);
  return 1;
}

/***
 * @function result:flags()
 * @desc Get the flags
 * @return flags[integer]
 * @ref http://docs.libmemcached.org/memcached_result_st.html#memcached_result_flags
*/
LUALIB_API int lmemcached_result_flags(lua_State *L) {
  lmemcached_result *self = lmemcached_result_check(L, 1);
  uint32_t flags = memcached_result_flags(self->ptr);
  lua_pushinteger(L, flags);
  return 1;
}

/***
 * @function result:cas()
 * @desc Get the cas
 * @return cas[integer]
 * @ref http://docs.libmemcached.org/memcached_result_st.html#memcached_result_cas
*/

LUALIB_API int lmemcached_result_cas(lua_State *L) {
  lmemcached_result *self = lmemcached_result_check(L, 1);
  uint64_t cas = memcached_result_cas(self->ptr);
  lua_pushinteger(L, cas);
  return 1;
}

/***
 * @function result:set_value(new_value)
 * @desc Set result value
 * @param new_value[string]
 * @return ok[booelan]
 * @return rc[integer]
 * @ref http://docs.libmemcached.org/memcached_result_st.html#memcached_result_set_value
*/
LUALIB_API int lmemcached_result_set_value(lua_State *L) {
  lmemcached_result *self = lmemcached_result_check(L, 1);
  size_t value_length;
  const char *value = luaL_tolstring(L, 2, &value_length);
  memcached_return_t rc = memcached_result_set_value(self->ptr, value, value_length);
  bool brc = memcached_success(rc);
  lua_pushboolean(L, brc);
  lua_pushinteger(L, rc);
  return 2;
}

/***
 * @function result:set_flags(new_flags)
 * @desc Set result flags
 * @param new_flags[integer]
 * @ref http://docs.libmemcached.org/memcached_result_st.html#memcached_result_set_flags
*/
LUALIB_API int lmemcached_result_set_flags(lua_State *L) {
  lmemcached_result *self = lmemcached_result_check(L, 1);
  uint32_t flags = luaL_checkinteger(L, 2);
  memcached_result_set_flags(self->ptr, flags);
  return 0;
}

/***
 * @function result:set_expiration(new_expiration)
 * @desc Set result expiration
 * @param new_expiration[integer]
 * @ref http://docs.libmemcached.org/memcached_result_st.html#memcached_result_set_expiration
*/
LUALIB_API int lmemcached_result_set_expiration(lua_State *L) {
  lmemcached_result *self = lmemcached_result_check(L, 1);
  time_t expiration = (time_t) luaL_checkinteger(L, 2);
  memcached_result_set_expiration(self->ptr, expiration);
  return 0;
}

static luaL_Reg lmemcached_result_methods[] = {
  { "key", lmemcached_result_key },
  { "value", lmemcached_result_value },
  { "flags", lmemcached_result_flags },
  { "cas", lmemcached_result_cas },
  { "set_value", lmemcached_result_set_value },
  { "set_flags", lmemcached_result_set_flags },
  { "set_expiration", lmemcached_result_set_expiration },
  { "__index", lmemcached_result_index },
  { "__gc", lmemcached_result_free },
  { NULL, NULL },
};

LUALIB_API void lmemcached_result_open(lua_State *L) {
  lmemcached_createmeta(L, LMEMCACHED_RESULT_MT, lmemcached_result_methods);
}

