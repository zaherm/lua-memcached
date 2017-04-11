# lua-memcached
Lua binding for [libmemcached](http://libmemcached.org/).

## Example
```lua
local memcached = require("memcached")
local memc = memcached.new("--SERVER=localhost")
local ok, res = memc:set("some_key", "some_value")
ok, res = memc:delete("some_key")
```

## Doc
See [**memcached**](doc/memcached.md)

