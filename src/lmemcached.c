#include "lmemcached.h"

lmemcached *lmemcached_check(lua_State *L, int index) {
  lmemcached *m = (lmemcached *) luaL_checkudata(L, index, LMEMCACHED_MT);
  luaL_argcheck(L, m != NULL && m->ptr != NULL, index, LMEMCACHED_MT" expected");
  return m;
}

/***
 * @function memcached.new(option_string)
 * @param option_string[string] - options string
 * @desc Initialize a new instances of memcached.
 * @return memcached[memcached] - new memcached instance.
*/
LUALIB_API int lmemcached_new(lua_State *L) {
  size_t string_length;
  const char *option_string = luaL_checklstring(L, 1, &string_length);
  lmemcached *m = (lmemcached *) lua_newuserdata(L, sizeof(lmemcached));
  m->ptr = memcached(option_string, string_length);
  lmemcached_setmeta(L, LMEMCACHED_MT);
  return 1;
}

LUALIB_API int lmemcached_create(lua_State *L) {
  lmemcached *m = (lmemcached *) lua_newuserdata(L, sizeof(lmemcached));
  m->ptr = memcached_create(NULL);
  lmemcached_setmeta(L, LMEMCACHED_MT);
  return 1;
}

/***
 * @function memcached:free()
 * @desc Free memcached instance allocated memory (called on __gc).
*/
LUALIB_API int lmemcached_free(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  if(self->ptr != NULL) {
    memcached_free(self->ptr);
    self->ptr = NULL;
  }
  return 0;
}

LUALIB_API int lmemcached_index(lua_State *L) {
  const char* key = luaL_checkstring(L, 2);
  lua_getmetatable(L, 1);
  lua_getfield(L, -1, key);
  /* return if the key present in the metatable */
  if(!lua_isnil(L, -1)) {
    return 1;
  }
  return 0;
}
/***
 * @function memcached:strerror()
 * @desc Get string representation of the last error.
 * @return error[string].
*/
LUALIB_API int lmemcached_strerror(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  memcached_return_t rc = (memcached_return_t) luaL_checkint(L, 2);
  const char *error = memcached_strerror(self->ptr, rc);
  lua_pushstring(L, error);
  return 1;
}

/***
 * @function memcached:clone()
 * @desc Clone a memcached instance.
 * @return clone[memcached] - A cloned memcached instance.
*/
LUALIB_API int lmemcached_clone(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  lmemcached *m = (lmemcached *) lua_newuserdata(L, sizeof(lmemcached));
  m->ptr = memcached_clone(NULL, self->ptr);
  lmemcached_setmeta(L, LMEMCACHED_MT);
  return 1;
}

/***
 * @function memcached:servers_reset()
 * @desc Reset servers list from memcached instnace.
*/
LUALIB_API int lmemcached_servers_reset(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  memcached_servers_reset(self->ptr);
  return 0;
}

/***
 * @function memcached:last_error_message()
 * @desc Get last error message.
 * @return error_message[string] - Error message string or nil.
*/
LUALIB_API int lmemcached_last_error_message(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  const char *err = memcached_last_error_message(self->ptr);
  if(err != NULL) {
    lua_pushstring(L, err);
  }
  else {
    lua_pushnil(L);
  }
  return 1;
}

/***
 * @function memcached:increment(key, offset [, initial, expiration])
 * @desc Increments a key with given offset.
 * @param key[string]
 * @param offset[integer]
 * @param initial[integer] - optional - initial value if key does not exist.
 * @param expiration[timestamp] - optional - expiration timestamp (integer representation).
 * @return ok[boolean] - true if successful, false otherwise
 * @return value[integer] - new value after the operation or return code if failed.
*/
LUALIB_API int lmemcached_increment(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  size_t key_length;
  const char *key = luaL_checklstring(L, 2, &key_length);
  uint32_t offset = (uint32_t) luaL_checknumber(L, 3);
  uint64_t value;
  memcached_return_t rc;
  int nargs = lua_gettop(L);
  lmemcached_assert(L, (nargs == 3 || nargs == 5), "unexpected number of arguments");
  if(nargs == 3) {
    rc = memcached_increment(self->ptr, key, key_length, offset, &value);
  }
  else if(nargs == 5) {
    uint64_t initial = (uint64_t) luaL_checkinteger(L, 4);
    time_t expiration = (time_t) luaL_checknumber(L, 5);
    rc = memcached_increment_with_initial(self->ptr, key, key_length, offset, initial, expiration, &value);
  }
  bool brc = memcached_success(rc);
  lua_pushboolean(L, brc);
  lua_pushinteger(L, brc ? value : rc);
  return 2;
}

/***
 * @function memcached:decrement(key, offset [, initial, expiration])
 * @desc Decrements a key with given offset.
 * @parma key[string]
 * @param offset[integer]
 * @param initial[integer] - optional - initial value if key does not exist.
 * @param expiration[timestamp] - optional - expiration timestamp (integer representation).
 * @return ok[boolean] - true if successful, false otherwise
 * @return value[integer] - new value after the operation or return code if failed.
*/
LUALIB_API int lmemcached_decrement(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  size_t key_length;
  const char *key = luaL_checklstring(L, 2, &key_length);
  uint32_t offset = (uint32_t) luaL_checknumber(L, 3);
  uint64_t value;
  memcached_return_t rc;
  int nargs = lua_gettop(L);
  lmemcached_assert(L, (nargs == 3 || nargs == 5), "unexpected number of arguments");
  if(nargs == 3) {
    rc = memcached_decrement(self->ptr, key, key_length, offset, &value);
  }
  else if(nargs == 5) {
    uint64_t initial = (uint64_t) luaL_checkinteger(L, 4);
    time_t expiration = (time_t) luaL_checknumber(L, 5);
    rc = memcached_decrement_with_initial(self->ptr, key, key_length, offset, initial, expiration, &value);
  }

  bool brc = memcached_success(rc);
  lua_pushboolean(L, brc);
  lua_pushinteger(L, brc ? value : rc);
  return 2;
}

/***
 * @function memcached:increment_by_key(group_key, key, offset [, initial, expiration])
 * @desc Increments a key with given offset in a group_key.
 * @param group_key[string]
 * @param key[string]
 * @param offset[integer]
 * @param initial[integer] - optional - initial value if key does not exist.
 * @param expiration[timestamp] - optional - expiration timestamp (integer representation).
 * @return ok[boolean] - true if successful, false otherwise
 * @return value[integer] - new value after the operation or return code if failed.
*/
LUALIB_API int lmemcached_increment_by_key(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  size_t group_key_length, key_length;
  const char *group_key = luaL_checklstring(L, 2, &group_key_length);
  const char *key = luaL_checklstring(L, 3, &key_length);
  uint32_t offset = (uint32_t) luaL_checknumber(L, 4);
  uint64_t value;
  memcached_return_t rc;
  int nargs = lua_gettop(L);
  lmemcached_assert(L, (nargs == 4 || nargs == 6), "unexpected number of arguments");
  if(nargs == 4) {
    rc = memcached_increment_by_key(self->ptr, group_key, group_key_length, key, key_length, offset, &value);
  }
  else if(nargs == 6) {
    uint64_t initial = (uint64_t) luaL_checkinteger(L, 5);
    time_t expiration = (time_t) luaL_checknumber(L, 6);
    rc = memcached_increment_with_initial_by_key(self->ptr, group_key, group_key_length, key, key_length, offset, initial, expiration, &value);
  }
  bool brc = memcached_success(rc);
  lua_pushboolean(L, brc);
  lua_pushinteger(L, brc ? value : rc);
  return 2;
}

/***
 * @function memcached:increment_by_key(group_key, key, offset [, initial, expiration])
 * @desc Decrements a key with given offset in a group_key.
 * @param group_key[string]
 * @param key[string]
 * @param offset[integer]
 * @param initial[integer] - optional - initial value if key does not exist.
 * @param expiration[timestamp] - optional - expiration timestamp (integer representation).
 * @return ok[boolean] - true if successful, false otherwise
 * @return value[integer] - new value after the operation or return code if failed.
*/
LUALIB_API int lmemcached_decrement_by_key(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  size_t group_key_length, key_length;
  const char *group_key = luaL_checklstring(L, 2, &group_key_length);
  const char *key = luaL_checklstring(L, 3, &key_length);
  uint32_t offset = (uint32_t) luaL_checknumber(L, 4);
  uint64_t value;
  memcached_return_t rc;
  int nargs = lua_gettop(L);
  lmemcached_assert(L, (nargs == 4 || nargs == 6), "unexpected number of arguments");
  if(nargs == 4) {
    rc = memcached_decrement_by_key(self->ptr, group_key, group_key_length, key, key_length, offset, &value);
  }
  else if(nargs == 6) {
    uint64_t initial = (uint64_t) luaL_checkinteger(L, 5);
    time_t expiration = (time_t) luaL_checknumber(L, 6);
    rc = memcached_decrement_with_initial_by_key(self->ptr, group_key, group_key_length, key, key_length, offset, initial, expiration, &value);
  }
  bool brc = memcached_success(rc);
  lua_pushboolean(L, brc);
  lua_pushinteger(L, brc ? value : rc);
  return 2;
}

/***
 * @function memcached:delete(key, expiration)
 * @desc Deletes a key.
 * @param key[string] - key to delete
 * @param expiration[integer] - expiration time
 * @return ok[boolean] - result status
 * @return rc[integer] - result code
 * @ref http://docs.libmemcached.org/memcached_delete.html
*/
LUALIB_API int lmemcached_delete(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  size_t key_length;
  const char *key = luaL_checklstring(L, 2, &key_length);
  time_t expiration = (time_t) luaL_checknumber(L, 3);
  memcached_return_t rc = memcached_delete(self->ptr, key, key_length, expiration);
  bool brc = memcached_success(rc);
  lua_pushboolean(L, brc);
  lua_pushinteger(L, rc);
  return 2;
}

/***
 * @function memcached:delete_by_key(group_key, key, expiration)
 * @desc Deletes a key from a group.
 * @param group_key[string] - key to delete
 * @param key[string] - key to delete
 * @param expiration[integer] - expiration time
 * @return ok[boolean] - result status
 * @return rc[integer] - result code
 * @ref http://docs.libmemcached.org/memcached_delete.html
*/
LUALIB_API int lmemcached_delete_by_key(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  size_t group_key_length, key_length;
  const char *group_key = luaL_checklstring(L, 2, &group_key_length);
  const char *key = luaL_checklstring(L, 3, &key_length);
  time_t expiration = (time_t) luaL_checknumber(L, 4);
  memcached_return_t rc = memcached_delete_by_key(self->ptr, group_key, group_key_length, key, key_length, expiration);
  bool brc = memcached_success(rc);
  lua_pushboolean(L, brc);
  lua_pushinteger(L, rc);
  return 2;
}

/***
 * @function memcached:exist(key)
 * @desc Check if a key exists.
 * @param key[string]
 * @return ok[boolean] - result status (true if key exists, false otherwise)
 * @return rc[integer] - result code
 * @ref http://docs.libmemcached.org/memcached_exist.html
*/
LUALIB_API int lmemcached_exist(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  size_t key_length;
  const char *key = luaL_checklstring(L, 2, &key_length);
  memcached_return_t rc = memcached_exist(self->ptr, key, key_length);
  bool brc = memcached_success(rc);
  lua_pushboolean(L, brc);
  lua_pushinteger(L, rc);
  return 2;
}

/***
 * @function memcached:exist_by_key(group_key, key)
 * @desc Check if a key exists by group_key.
 * @param group_key[string]
 * @param key[string]
 * @return ok[boolean] - result status (true if key exists, false otherwise)
 * @return rc[integer] - result code
 * @ref http://docs.libmemcached.org/memcached_exist.html
*/
LUALIB_API int lmemcached_exist_by_key(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  size_t group_key_length, key_length;
  const char *group_key = luaL_checklstring(L, 2, &group_key_length);
  const char *key = luaL_checklstring(L, 3, &key_length);
  memcached_return_t rc = memcached_exist_by_key(self->ptr, group_key, group_key_length, key, key_length);
  bool brc = memcached_success(rc);
  lua_pushboolean(L, brc);
  lua_pushinteger(L, rc);
  return 2;
}

/***
 * @function memcached:flush_buffers()
 * @desc Flush all buffers by sending buffered commands.
 * @return ok[boolean] - result status
 * @return rc[integer] - result code
 * @ref http://docs.libmemcached.org/memcached_flush_buffers.html
*/
LUALIB_API int lmemcached_flush_buffers(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  memcached_return_t rc = memcached_flush_buffers(self->ptr);
  bool brc = memcached_success(rc);
  lua_pushboolean(L, brc);
  lua_pushinteger(L, rc);
  return 2;
}

/***
 * @function memcached:flush(expiration)
 * @desc Flush all buffers by sending buffered commands.
 * @param expiration[timestamp] - Expiration timestamp (0 - immediate flush!)
 * @return ok[boolean] - result status
 * @return rc[integer] - result code
 * @ref http://docs.libmemcached.org/memcached_flush.html
*/
LUALIB_API int lmemcached_flush(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  time_t expiration = (time_t) luaL_checkinteger(L, 2);
  memcached_return_t rc = memcached_flush(self->ptr, expiration);
  bool brc = memcached_success(rc);
  lua_pushboolean(L, brc);
  lua_pushinteger(L, rc);
  return 2;
}

/***
 * @function memcached:get(key)
 * @desc Get the value of key from the server.
 * @param key[any] - will be casted to string!
 * @return ok[boolean] - result status
 * @return rc[string/integer] - returns the value (string) or return code
 * @return flags[integer] - flags were stored with the value
 * @ref http://docs.libmemcached.org/memcached_get.html
*/
LUALIB_API int lmemcached_get(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  size_t key_length, value_length;
  const char *key = luaL_tolstring(L, 2, &key_length);
  uint32_t flags;
  memcached_return_t rc;
  char *value = memcached_get(self->ptr, key, key_length, &value_length, &flags, &rc);
  bool brc = memcached_success(rc);
  lua_pushboolean(L, brc);
  if(brc) {
    lua_pushlstring(L, value, value_length);
    free(value);
    lua_pushinteger(L, flags);
  }
  else {
    lua_pushinteger(L, rc);
    lua_pushnil(L);
  }
  return 3;
}

/***
 * @function memcached:get_by_key(group_key, key)
 * @desc Get the value of key from the server.
 * @param group_key[any] - will be casted to string!
 * @param key[any] - will be casted to string!
 * @return ok[boolean] - result status
 * @return rc[string/integer] - returns the value (string) or return code
 * @return flags[integer] - flags were stored with the value
 * @ref http://docs.libmemcached.org/memcached_get_by_key.html
*/
LUALIB_API int lmemcached_get_by_key(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  size_t group_key_length ,key_length, value_length;
  const char *group_key = luaL_tolstring(L, 2, &group_key_length);
  const char *key = luaL_tolstring(L, 3, &key_length);
  uint32_t flags;
  memcached_return_t rc;
  char *value = memcached_get_by_key(self->ptr, group_key, group_key_length, key, key_length, &value_length, &flags, &rc);
  bool brc = memcached_success(rc);
  lua_pushboolean(L, brc);
  if(brc) {
    lua_pushlstring(L, value, value_length);
    free(value);
    lua_pushinteger(L, flags);
  }
  else {
    lua_pushinteger(L, rc);
    lua_pushnil(L);
  }
  return 3;
}


/***
 * @function memcached:mget(key1, key2, ...)
 * @desc Get multiple keys vlaues, in order to fetch the results use memcached:fetch_result()
 * @param key#[any] - will be casted to string!
 * @return ok[boolean] - result status
 * @return rc[string/integer] - returns the value (string) or return code
 * @ref http://docs.libmemcached.org/memcached_get.html#memcached_mget
*/
LUALIB_API int lmemcached_mget(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  size_t number_of_keys = lua_gettop(L) - 1;
  const char *keys[number_of_keys];
  size_t keys_length[number_of_keys];
  memcached_return_t rc;
  size_t i;
  lmemcached_assert(L, number_of_keys >= 1, "Expected at least one key!");
  for(i = 0; i < number_of_keys; i++) {
    keys[i] = lua_tolstring(L, i + 2, &keys_length[i]);
  }
  rc = memcached_mget(self->ptr, keys, keys_length, number_of_keys);
  bool brc = memcached_success(rc);
  lua_pushboolean(L, brc);
  lua_pushinteger(L, rc);
  return 2;
}

/***
 * @function memcached:mget_by_key(group_key, key1, key2, ...)
 * @desc Get multiple keys by group_key, in order to fetch the results use memcached:fetch_result()
 * @param group_key[any] - will be casted to string!
 * @param key#[any] - will be casted to string!
 * @return ok[boolean] - result status
 * @return rc[string/integer] - returns the value (string) or return code
 * @ref http://docs.libmemcached.org/memcached_get.html#memcached_mget_by_key
*/
LUALIB_API int lmemcached_mget_by_key(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  size_t group_key_length;
  const char *group_key = lua_tolstring(L, 2, &group_key_length);
  size_t number_of_keys = lua_gettop(L) - 2;
  lmemcached_assert(L, number_of_keys >= 1, "Expected at least one key!");
  const char *keys[number_of_keys];
  size_t keys_length[number_of_keys];
  memcached_return_t rc;
  size_t i;
  for(i = 0; i < number_of_keys; i++) {
    keys[i] = lua_tolstring(L, i + 3, &keys_length[i]);
  }
  rc = memcached_mget_by_key(self->ptr, group_key, group_key_length, keys, keys_length, number_of_keys);
  bool brc = memcached_success(rc);
  lua_pushboolean(L, brc);
  lua_pushinteger(L, rc);
  return 2;
}


/***
 * @function memcached:fetch_result()
 * @desc Create a result object, should be called after memcached:mget.
 * @return ok[boolean] - result status
 * @return result[memcached.result] - result object or error code. See [**result**](result.md) for more information.
 * @ref http://docs.libmemcached.org/memcached_get.html#memcached_mget
*/
LUALIB_API int lmemcached_fetch_result(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  memcached_return_t rc;
  memcached_result_st *st = memcached_fetch_result(self->ptr, NULL, &rc);
  bool brc = memcached_success(rc);
  lua_pushboolean(L, brc);
  if(brc) {
    lmemcached_result *r = (lmemcached_result *) lua_newuserdata(L, sizeof(lmemcached_result));
    r->ptr = st;
    lmemcached_setmeta(L, LMEMCACHED_RESULT_MT);
  }
  else {
    lua_pushinteger(L, rc);
    if(st != NULL) {
      memcached_result_free(st);
    }
  }

  return 2;
}
/* set */

/***
 * @function memcached:set(key, value [, expiration=0, flags=0])
 * @desc Set value with optional expiration and flags
 * @param key[string]
 * @param value[string]
 * @param expiration[timestamp] - optional, default: 0 (none)
 * @param flags[integer] - optional, default: 0 (none)
 * @return ok[boolean] - result status
 * @return rc[integer] - return code
 * @ref http://docs.libmemcached.org/memcached_set.html#memcached_set
*/
LUALIB_API int lmemcached_set(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  size_t key_length, value_length;
  const char *key = lua_tolstring(L, 2, &key_length);
  const char *value = lua_tolstring(L, 3, &value_length);
  time_t expiration = (time_t) luaL_optinteger(L, 4, 0);
  uint32_t flags = luaL_optinteger(L, 5, 0);
  memcached_return_t rc = memcached_set(self->ptr, key, key_length, value, value_length, expiration, flags);
  bool brc = memcached_success(rc);
  lua_pushboolean(L, brc);
  lua_pushinteger(L, rc);
  return 2;
}

/***
 * @function memcached:set_by_key(group_key, key, value [, expiration=0, flags=0])
 * @desc Set value by group_key, with optional expiration and flags
 * @param group_key[string]
 * @param key[string]
 * @param value[string]
 * @param expiration[timestamp] - optional, default: 0 (none)
 * @param flags[integer] - optional, default: 0 (none)
 * @return ok[boolean] - result status
 * @return rc[integer] - return code
 * @ref http://docs.libmemcached.org/memcached_set.html#memcached_set_by_key
*/
LUALIB_API int lmemcached_set_by_key(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  size_t group_key_length, key_length, value_length;
  const char *group_key = lua_tolstring(L, 2, &group_key_length);
  const char *key = lua_tolstring(L, 3, &key_length);
  const char *value = lua_tolstring(L, 4, &value_length);
  time_t expiration = (time_t) luaL_optinteger(L, 5, 0);
  uint32_t flags = luaL_optinteger(L, 6, 0);
  memcached_return_t rc = memcached_set_by_key(self->ptr, group_key, group_key_length, key, key_length, value, value_length, expiration, flags);
  bool brc = memcached_success(rc);
  lua_pushboolean(L, brc);
  lua_pushinteger(L, rc);
  return 2;
}


/***
 * @function memcached:add(key, value [, expiration=0, flags=0])
 * @desc Add a value with optional expiration and flags
 * @param key[string]
 * @param value[string]
 * @param expiration[timestamp] - optional, default: 0 (none)
 * @param flags[integer] - optional, default: 0 (none)
 * @return ok[boolean] - result status
 * @return rc[integer] - return code
 * @ref http://docs.libmemcached.org/memcached_set.html#memcached_add
*/
LUALIB_API int lmemcached_add(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  size_t key_length, value_length;
  const char *key = lua_tolstring(L, 2, &key_length);
  const char *value = lua_tolstring(L, 3, &value_length);
  time_t expiration = (time_t) luaL_optinteger(L, 4, 0);
  uint32_t flags = luaL_optinteger(L, 5, 0);
  memcached_return_t rc = memcached_add(self->ptr, key, key_length, value, value_length, expiration, flags);
  bool brc = memcached_success(rc);
  lua_pushboolean(L, brc);
  lua_pushinteger(L, rc);
  return 2;
}

/***
 * @function memcached:add_by_key(group_key, key, value [, expiration=0, flags=0])
 * @desc Add a value by group_key, with optional expiration and flags
 * @param group_key[string]
 * @param key[string]
 * @param value[string]
 * @param expiration[timestamp] - optional, default: 0 (none)
 * @param flags[integer] - optional, default: 0 (none)
 * @return ok[boolean] - result status
 * @return rc[integer] - return code
 * @ref http://docs.libmemcached.org/memcached_set.html#memcached_add_by_key
*/
LUALIB_API int lmemcached_add_by_key(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  size_t group_key_length, key_length, value_length;
  const char *group_key = lua_tolstring(L, 2, &group_key_length);
  const char *key = lua_tolstring(L, 3, &key_length);
  const char *value = lua_tolstring(L, 4, &value_length);
  time_t expiration = (time_t) luaL_optinteger(L, 5, 0);
  uint32_t flags = luaL_optinteger(L, 6, 0);
  memcached_return_t rc = memcached_add_by_key(self->ptr, group_key, group_key_length, key, key_length, value, value_length, expiration, flags);
  bool brc = memcached_success(rc);
  lua_pushboolean(L, brc);
  lua_pushinteger(L, rc);
  return 2;
}

/***
 * @function memcached:replace(key, value [, expiration=0, flags=0])
 * @desc Replace a key value with optional expiration and flags
 * @param key[string]
 * @param value[string]
 * @param expiration[timestamp] - optional, default: 0 (none)
 * @param flags[integer] - optional, default: 0 (none)
 * @return ok[boolean] - result status
 * @return rc[integer] - return code
 * @ref http://docs.libmemcached.org/memcached_set.html#memcached_replace
*/
LUALIB_API int lmemcached_replace(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  size_t key_length, value_length;
  const char *key = lua_tolstring(L, 2, &key_length);
  const char *value = lua_tolstring(L, 3, &value_length);
  time_t expiration = (time_t) luaL_optinteger(L, 4, 0);
  uint32_t flags = luaL_optinteger(L, 5, 0);
  memcached_return_t rc = memcached_replace(self->ptr, key, key_length, value, value_length, expiration, flags);
  bool brc = memcached_success(rc);
  lua_pushboolean(L, brc);
  lua_pushinteger(L, rc);
  return 2;
}

/***
 * @function memcached:replace_by_key(group_key, key, value [, expiration=0, flags=0])
 * @desc Replac a key value by group_key, with optional expiration and flags
 * @param group_key[string]
 * @param key[string]
 * @param value[string]
 * @param expiration[timestamp] - optional, default: 0 (none)
 * @param flags[integer] - optional, default: 0 (none)
 * @return ok[boolean] - result status
 * @return rc[integer] - return code
 * @ref http://docs.libmemcached.org/memcached_set.html#memcached_replace_by_key
*/
LUALIB_API int lmemcached_replace_by_key(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  size_t group_key_length, key_length, value_length;
  const char *group_key = lua_tolstring(L, 2, &group_key_length);
  const char *key = lua_tolstring(L, 3, &key_length);
  const char *value = lua_tolstring(L, 4, &value_length);
  time_t expiration = (time_t) luaL_optinteger(L, 5, 0);
  uint32_t flags = luaL_optinteger(L, 6, 0);
  memcached_return_t rc = memcached_replace_by_key(self->ptr, group_key, group_key_length, key, key_length, value, value_length, expiration, flags);
  bool brc = memcached_success(rc);
  lua_pushboolean(L, brc);
  lua_pushinteger(L, rc);
  return 2;
}

/* append/prepend */

/***
 * @function memcached:prepend(key, value [, expiration=0, flags=0])
 * @desc Prepend to the value of key with optional expiration and flags
 * @param key[string]
 * @param value[string]
 * @param expiration[timestamp] - optional, default: 0 (none)
 * @param flags[integer] - optional, default: 0 (none)
 * @return ok[boolean] - result status
 * @return rc[integer] - return code
 * @ref http://docs.libmemcached.org/memcached_append.html#memcached_prepend
*/
LUALIB_API int lmemcached_prepend(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  size_t key_length, value_length;
  const char *key = lua_tolstring(L, 2, &key_length);
  const char *value = lua_tolstring(L, 3, &value_length);
  time_t expiration = (time_t) luaL_optinteger(L, 4, 0);
  uint32_t flags = luaL_optinteger(L, 5, 0);
  memcached_return_t rc = memcached_prepend(self->ptr, key, key_length, value, value_length, expiration, flags);
  bool brc = memcached_success(rc);
  lua_pushboolean(L, brc);
  lua_pushinteger(L, rc);
  return 2;
}

/***
 * @function memcached:prepend_by_key(group_key, key, value [, expiration=0, flags=0])
 * @desc Prepend to the value by group_key, with optional expiration and flags
 * @param group_key[string]
 * @param key[string]
 * @param value[string]
 * @param expiration[timestamp] - optional, default: 0 (none)
 * @param flags[integer] - optional, default: 0 (none)
 * @return ok[boolean] - result status
 * @return rc[integer] - return code
 * @ref http://docs.libmemcached.org/memcached_append.html#memcached_prepend_by_key
*/
LUALIB_API int lmemcached_prepend_by_key(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  size_t group_key_length, key_length, value_length;
  const char *group_key = lua_tolstring(L, 2, &group_key_length);
  const char *key = lua_tolstring(L, 3, &key_length);
  const char *value = lua_tolstring(L, 4, &value_length);
  time_t expiration = (time_t) luaL_optinteger(L, 5, 0);
  uint32_t flags = luaL_optinteger(L, 6, 0);
  memcached_return_t rc = memcached_prepend_by_key(self->ptr, group_key, group_key_length, key, key_length, value, value_length, expiration, flags);
  bool brc = memcached_success(rc);
  lua_pushboolean(L, brc);
  lua_pushinteger(L, rc);
  return 2;
}

/***
 * @function memcached:append(key, value [, expiration=0, flags=0])
 * @desc Append to the value of key with optional expiration and flags
 * @param key[string]
 * @param value[string]
 * @param expiration[timestamp] - optional, default: 0 (none)
 * @param flags[integer] - optional, default: 0 (none)
 * @return ok[boolean] - result status
 * @return rc[integer] - return code
 * @ref http://docs.libmemcached.org/memcached_append.html#memcached_append
*/
LUALIB_API int lmemcached_append(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  size_t key_length, value_length;
  const char *key = lua_tolstring(L, 2, &key_length);
  const char *value = lua_tolstring(L, 3, &value_length);
  time_t expiration = (time_t) luaL_optinteger(L, 4, 0);
  uint32_t flags = luaL_optinteger(L, 5, 0);
  memcached_return_t rc = memcached_append(self->ptr, key, key_length, value, value_length, expiration, flags);
  bool brc = memcached_success(rc);
  lua_pushboolean(L, brc);
  lua_pushinteger(L, rc);
  return 2;
}

/***
 * @function memcached:append_by_key(group_key, key, value [, expiration=0, flags=0])
 * @desc Append to the value by group_key, with optional expiration and flags
 * @param group_key[string]
 * @param key[string]
 * @param value[string]
 * @param expiration[timestamp] - optional, default: 0 (none)
 * @param flags[integer] - optional, default: 0 (none)
 * @return ok[boolean] - result status
 * @return rc[integer] - return code
 * @ref http://docs.libmemcached.org/memcached_append.html#memcached_append_by_key
*/
LUALIB_API int lmemcached_append_by_key(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  size_t group_key_length, key_length, value_length;
  const char *group_key = lua_tolstring(L, 2, &group_key_length);
  const char *key = lua_tolstring(L, 3, &key_length);
  const char *value = lua_tolstring(L, 4, &value_length);
  time_t expiration = (time_t) luaL_optinteger(L, 5, 0);
  uint32_t flags = luaL_optinteger(L, 6, 0);
  memcached_return_t rc = memcached_append_by_key(self->ptr, group_key, group_key_length, key, key_length, value, value_length, expiration, flags);
  bool brc = memcached_success(rc);
  lua_pushboolean(L, brc);
  lua_pushinteger(L, rc);
  return 2;
}


/* cas */
/***
 * @function memcached:cas(key, value [, expiration=0, flags=0, cas=0])
 * @desc Overwrite the data on the server as long as "cas" is the same.
 * @param key[string]
 * @param value[string]
 * @param expiration[timestamp] - optional, default: 0 (none)
 * @param flags[integer] - optional, default: 0 (none)
 * @param cas[integer] - optional, default: 0 (none)
 * @return ok[boolean] - result status
 * @return rc[integer] - return code
 * @ref http://docs.libmemcached.org/memcached_cas.html#memcached_cas
*/
LUALIB_API int lmemcached_cas(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  size_t key_length, value_length;
  const char *key = lua_tolstring(L, 2, &key_length);
  const char *value = lua_tolstring(L, 3, &value_length);
  time_t expiration = (time_t) luaL_optinteger(L, 4, 0);
  uint32_t flags = luaL_optinteger(L, 5, 0);
  uint64_t cas = luaL_optinteger(L, 6, 0);
  memcached_return_t rc = memcached_cas(self->ptr, key, key_length, value, value_length, expiration, flags, cas);
  bool brc = memcached_success(rc);
  lua_pushboolean(L, brc);
  lua_pushinteger(L, rc);
  return 2;
}

/***
 * @function memcached:cas_by_key(group_key, key, value [, expiration=0, flags=0, cas=0])
 * @desc Overwrite the data on the server as long as "cas" is the same using group_key.
 * @param group_key[string]
 * @param key[string]
 * @param value[string]
 * @param expiration[timestamp] - optional, default: 0 (none)
 * @param flags[integer] - optional, default: 0 (none)
 * @param cas[integer] - optional, default: 0 (none)
 * @return ok[boolean] - result status
 * @return rc[integer] - return code
 * @ref http://docs.libmemcached.org/memcached_cas.html#memcached_cas_by_key
*/
LUALIB_API int lmemcached_cas_by_key(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  size_t group_key_length, key_length, value_length;
  const char *group_key = lua_tolstring(L, 2, &group_key_length);
  const char *key = lua_tolstring(L, 3, &key_length);
  const char *value = lua_tolstring(L, 4, &value_length);
  time_t expiration = (time_t) luaL_optinteger(L, 5, 0);
  uint32_t flags = luaL_optinteger(L, 6, 0);
  uint64_t cas = luaL_optinteger(L, 7, 0);
  memcached_return_t rc = memcached_cas_by_key(self->ptr, group_key, group_key_length, key, key_length, value, value_length, expiration, flags, cas);
  bool brc = memcached_success(rc);
  lua_pushboolean(L, brc);
  lua_pushinteger(L, rc);
  return 2;
}

/***
 * @function memcached:set_encoding_key(encoding_key)
 * @desc Set the encoding key (currenty only AES is supported).
 * @param encoding_key[string]
 * @ref http://docs.libmemcached.org/libmemcached-1.0/memcached_set_encoding_key.html#memcached_set_encoding_key
*/
LUALIB_API int lmemcached_set_encoding_key(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  size_t string_length;
  const char *string = lua_tolstring(L, 2, &string_length);
  memcached_set_encoding_key(self->ptr, string, string_length);
  return 0;
}

/***
 * @function memcached:quit()
 * @desc Disconnect from all connected servers.
 * @ref http://docs.libmemcached.org/memcached_quit.html
*/
LUALIB_API int lmemcached_quit(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  memcached_quit(self->ptr);
  return 0;
}

/***
 * @function memcached:behavior_get(flag)
 * @desc Get behavior by flag.
 * @param flag[integer] - Select from memcached.BEHAVIOR table
 * @return behavior[integer] - Behavior value
 * @ref http://docs.libmemcached.org/memcached_behavior.html#memcached_behavior_get
*/
LUALIB_API int lmemcached_behavior_get(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  memcached_behavior_t flag = luaL_checkinteger(L, 2);
  uint64_t behavior = memcached_behavior_get(self->ptr, flag);
  lua_pushinteger(L, behavior);
  return 1;
}

/***
 * @function memcached:behavior_set(flag, data)
 * @desc Set behavior value.
 * @param flag[integer] - Select from memcached.BEHAVIOR table
 * @param data[integer] - Behavior data to set
 * @return ok[booelan]
 * @return rc[integer]
 * @ref http://docs.libmemcached.org/memcached_behavior.html#memcached_behavior_set
*/
LUALIB_API int lmemcached_behavior_set(lua_State *L) {
  lmemcached *self = lmemcached_check(L, 1);
  memcached_behavior_t flag = luaL_checkinteger(L, 2);
  uint64_t data = luaL_checkinteger(L, 3);
  memcached_return_t rc = memcached_behavior_set(self->ptr, flag, data);
  lua_pushboolean(L, memcached_success(rc));
  lua_pushinteger(L, rc);
  return 1;
}



/***
 * @function memcached.lib_version()
 * @desc Returns the libmemcached version.
 * @return version[string] - string representation of the libmemcached version.
 * @ref TODO
*/
LUALIB_API int lmemcached_lib_version(lua_State *L) {
  const char *lib_version = memcached_lib_version();
  lua_pushstring(L, lib_version);
  return 1;
}

/***
 * @function memcached.check_configuration(option_string)
 * @desc Checks configuration string
 * @param option_string[string] - Options string.
 * @return ok[booelan] - check result.
 * @return error[string] - error message if the check failed.
 * @ref http://docs.libmemcached.org/libmemcached_configuration.html#libmemcached_check_configuration
*/

LUALIB_API int lmemcached_check_configuration(lua_State *L) {
  size_t length;
  const char *option_string = luaL_checklstring(L, 1, &length);
  char buf[2048];
  memcached_return_t rc = libmemcached_check_configuration(option_string, length,
                                                           buf, sizeof(buf));
  bool brc = memcached_success(rc);
  lua_pushboolean(L, brc);
  if(brc) {
    lua_pushnil(L);
  }
  else {
    lua_pushstring(L, buf);
  }
  return 2;
}


LUALIB_API int luaopen_memcached(lua_State *L) {
  lua_newtable(L);
  /* non-metatable based functions */
  luaL_setfuncs(L, lmemcached_funcs, 0);
  /* metatable functions */
  lmemcached_createmeta(L, LMEMCACHED_MT, lmemcached_methods);
  lmemcached_result_open(L);

  lua_newtable(L);
  int i = 0;
  for(; lmemcached_const_behaviour[i].name != NULL; i++) {
    lua_pushinteger(L, lmemcached_const_behaviour[i].flag);
    lua_setfield(L, -2, lmemcached_const_behaviour[i].name);
  }
  lua_setfield(L, -2, "BEHAVIOR");
  lua_pushliteral(L, LMEMCACHED_VERSION);
  lua_setfield(L, -2, "_VERSION");
  lua_pushliteral(L, LMEMCACHED_COPYRIGHT);
  lua_setfield(L, -2, "_COPYRIGHT");
  lua_pushliteral(L, LMEMCACHED_DESCRIPTION);
  lua_setfield(L, -2, "_DESCRIPTION");
  return 1;
}

