local memcached = require("memcached")

assert(memcached.BEHAVIOR)
for k,v in pairs(memcached) do
  assert(k, v)
end

for k,v in pairs(memcached.BEHAVIOR) do
  assert(k, v)
end

for k,v in pairs(memcached.HASH) do
  assert(k, v)
end

