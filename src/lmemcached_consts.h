#ifndef LMEMCACHED_CONSTS_H
#define LMEMCACHED_CONSTS_H
#include <string.h>
#include "lauxlib.h"
#include "memcached.h"

struct lmemcached_consts_map {
  const char *name;
  uint64_t value;
};

void lmemcached_consts_push(lua_State *L, const char *name, const struct lmemcached_consts_map map[]);
void lmemcached_consts_open(lua_State *L);


#endif
