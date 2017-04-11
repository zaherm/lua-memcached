#include "lmemcached_consts.h"

void lmemcached_consts_push(lua_State *L, const char *name, const struct lmemcached_consts_map map[]) {
  lua_newtable(L);
  for(int i = 0; map[i].name != NULL; i++) {
    lua_pushinteger(L, map[i].value);
    lua_setfield(L, -2, map[i].name);
  }
  lua_setfield(L, -2, name);
}

const struct lmemcached_consts_map lmemcached_consts_behavior[] = {
  { "NO_BLOCK", MEMCACHED_BEHAVIOR_NO_BLOCK },
  { "TCP_NODELAY", MEMCACHED_BEHAVIOR_TCP_NODELAY },
  { "HASH", MEMCACHED_BEHAVIOR_HASH },
  { "KETAMA", MEMCACHED_BEHAVIOR_KETAMA },
  { "SOCKET_SEND_SIZE", MEMCACHED_BEHAVIOR_SOCKET_SEND_SIZE },
  { "SOCKET_RECV_SIZE", MEMCACHED_BEHAVIOR_SOCKET_RECV_SIZE },
  { "CACHE_LOOKUPS", MEMCACHED_BEHAVIOR_CACHE_LOOKUPS },
  { "SUPPORT_CAS", MEMCACHED_BEHAVIOR_SUPPORT_CAS },
  { "POLL_TIMEOUT", MEMCACHED_BEHAVIOR_POLL_TIMEOUT },
  { "DISTRIBUTION", MEMCACHED_BEHAVIOR_DISTRIBUTION },
  { "BUFFER_REQUESTS", MEMCACHED_BEHAVIOR_BUFFER_REQUESTS },
  { "USER_DATA", MEMCACHED_BEHAVIOR_USER_DATA },
  { "SORT_HOSTS", MEMCACHED_BEHAVIOR_SORT_HOSTS },
  { "VERIFY_KEY", MEMCACHED_BEHAVIOR_VERIFY_KEY },
  { "CONNECT_TIMEOUT", MEMCACHED_BEHAVIOR_CONNECT_TIMEOUT },
  { "RETRY_TIMEOUT", MEMCACHED_BEHAVIOR_RETRY_TIMEOUT },
  { "KETAMA_WEIGHTED", MEMCACHED_BEHAVIOR_KETAMA_WEIGHTED },
  { "KETAMA_HASH", MEMCACHED_BEHAVIOR_KETAMA_HASH },
  { "BINARY_PROTOCOL", MEMCACHED_BEHAVIOR_BINARY_PROTOCOL },
  { "SND_TIMEOUT", MEMCACHED_BEHAVIOR_SND_TIMEOUT },
  { "RCV_TIMEOUT", MEMCACHED_BEHAVIOR_RCV_TIMEOUT },
  { "SERVER_FAILURE_LIMIT", MEMCACHED_BEHAVIOR_SERVER_FAILURE_LIMIT },
  { "IO_MSG_WATERMARK", MEMCACHED_BEHAVIOR_IO_MSG_WATERMARK },
  { "IO_BYTES_WATERMARK", MEMCACHED_BEHAVIOR_IO_BYTES_WATERMARK },
  { "IO_KEY_PREFETCH", MEMCACHED_BEHAVIOR_IO_KEY_PREFETCH },
  { "HASH_WITH_PREFIX_KEY", MEMCACHED_BEHAVIOR_HASH_WITH_PREFIX_KEY },
  { "NOREPLY", MEMCACHED_BEHAVIOR_NOREPLY },
  { "USE_UDP", MEMCACHED_BEHAVIOR_USE_UDP },
  { "AUTO_EJECT_HOSTS", MEMCACHED_BEHAVIOR_AUTO_EJECT_HOSTS },
  { "NUMBER_OF_REPLICAS", MEMCACHED_BEHAVIOR_NUMBER_OF_REPLICAS },
  { "RANDOMIZE_REPLICA_READ", MEMCACHED_BEHAVIOR_RANDOMIZE_REPLICA_READ },
  { "CORK", MEMCACHED_BEHAVIOR_CORK },
  { "TCP_KEEPALIVE", MEMCACHED_BEHAVIOR_TCP_KEEPALIVE },
  { "TCP_KEEPIDLE", MEMCACHED_BEHAVIOR_TCP_KEEPIDLE },
  { "LOAD_FROM_FILE", MEMCACHED_BEHAVIOR_LOAD_FROM_FILE },
  { "REMOVE_FAILED_SERVERS", MEMCACHED_BEHAVIOR_REMOVE_FAILED_SERVERS },
  { "DEAD_TIMEOUT", MEMCACHED_BEHAVIOR_DEAD_TIMEOUT },
  { "SERVER_TIMEOUT_LIMIT", MEMCACHED_BEHAVIOR_SERVER_TIMEOUT_LIMIT },
  { "MAX", MEMCACHED_BEHAVIOR_MAX },
  { NULL, -1 }
};

const struct lmemcached_consts_map lmemcached_consts_hash[] = {
  { "DEFAULT", MEMCACHED_HASH_DEFAULT },
  { "MD5", MEMCACHED_HASH_MD5 },
  { "CRC", MEMCACHED_HASH_CRC },
  { "FNV1_64", MEMCACHED_HASH_FNV1_64 },
  { "FNV1A_64", MEMCACHED_HASH_FNV1A_64 },
  { "FNV1_32", MEMCACHED_HASH_FNV1_32 },
  { "FNV1A_32", MEMCACHED_HASH_FNV1A_32 },
  { "JENKINS", MEMCACHED_HASH_JENKINS },
  { "MURMUR", MEMCACHED_HASH_MURMUR },
  { "HSIEH", MEMCACHED_HASH_HSIEH },
  { "MURMUR3", MEMCACHED_HASH_MURMUR3 },
  { NULL, -1 }
};

void lmemcached_consts_open(lua_State *L) {
  lmemcached_consts_push(L, "BEHAVIOR", lmemcached_consts_behavior);
  lmemcached_consts_push(L, "HASH", lmemcached_consts_hash);
}

