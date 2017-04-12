local spec = require("test.spec").new()
local memcached = require("memcached")
local option_string = "--SERVER=localhost"

spec:describe("memcached:server_* functions", function(report)
  local memc = memcached.new(option_string)
  local ok, res
  report("server_count == 1", memc:server_count() == 1)
  ok, res = memc:server_add("localhost", 11211)
  report("server_add", ok)
  ok, res = memc:server_add_udp("localhost", 11211)
  report("server_add_udp", not ok) --deprecated?
  ok, res = memc:server_add_unix_socket("/tmp/memcached.sock")
  assert(ok)
end)

spec:describe("server:* functions", function(report)
  local memc = memcached.new(option_string)
  local ok, server
  report("server_count == 1", memc:server_count() == 1)
  ok, server = memc:server_by_key("test")
  report("server type", (server:type() == "TCP"))
  report("server port", server:port() == 11211)
end)


spec:run()


