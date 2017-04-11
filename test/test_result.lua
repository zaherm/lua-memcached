local spec = require("test.spec").new()
local memcached = require("memcached")
local option_string = "--SERVER=localhost"

spec:describe("memcached:mget()", function(report)
  local memc = memcached.new(option_string)
  local ok, rc, result
  ok, rc = memc:mget("x", "a", "b", "c")
  assert(ok)
  ok, result = memc:fetch_result()
  assert(ok)
  ok, result = memc:fetch_result()
  assert(ok)
  ok, result = memc:fetch_result()
  assert(ok)
  ok, result = memc:fetch_result()
  assert(not ok)
end)

spec:describe("memcached:mget_by_key()", function(report)
  local memc = memcached.new(option_string)
  local ok, rc, result
  local keys = { "a", "b", "c" }
  for _, key in ipairs(keys) do
    memc:set_by_key("group_key", key, key.."-value!")
  end
  ok, rc = memc:mget_by_key("group_key", "a", "b", "c")
  assert(ok)
  ok, result = memc:fetch_result()
  assert(ok)
  ok, result = memc:fetch_result()
  assert(ok)
end)

spec:describe("memcached:cas(), memcached:cas_by_key()", function(report)
  local memc = memcached.new(option_string.." --SUPPORT-CAS")
  local group_key = string.format("cas.by_key:%d", os.time())
  local ok, rc, result
  local key = string.format("cas:%d", os.time())
  ok, rc = memc:set(key, "value!", os.time() + 100)
  ok, rc = memc:mget(key)
  assert(ok)
  ok, result = memc:fetch_result()
  assert(ok)
  ok, rc = memc:cas(key, "new_value", os.time() + 100, 0, result:cas())
  report("with the same cas", ok)
  ok, rc = memc:cas(key, "new_value", 0, 0, 10)
  report("with different cas", not ok)
  ok, rc = memc:set_by_key(group_key, key, "value!")
  ok, rc = memc:mget_by_key(group_key, key)
  assert(ok)
  ok, result = memc:fetch_result()
  assert(ok)
  ok, rc = memc:cas_by_key(group_key, key, "new_value", os.time() + 100, 0, result:cas())
  report("with the same cas_by_key", ok)
  ok, rc = memc:cas_by_key(group_key, key, "new_value", 0, 0, 10)
  report("with different cas_by_key", not ok)
end)


spec:run()


