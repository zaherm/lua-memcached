### memcached

### memcached.new(option_string)
Initialize a new instances of memcached.

Params:
* option_string[string] - options string

Returns:
* memcached[memcached] - new memcached instance.

### memcached:free()
Free memcached instance allocated memory (called on __gc).

### memcached:strerror()
Get string representation of the last error.

Returns:
* error[string].

### memcached:clone()
Clone a memcached instance.

Returns:
* clone[memcached] - A cloned memcached instance.

### memcached:servers_reset()
Reset servers list from memcached instnace.

### memcached:last_error_message()
Get last error message.

Returns:
* error_message[string] - Error message string or nil.

### memcached:increment(key, offset [, initial, expiration])
Increments a key with given offset.

Params:
* key[string]
* offset[integer]
* initial[integer] - optional - initial value if key does not exist.
* expiration[timestamp] - optional - expiration timestamp (integer representation).

Returns:
* ok[boolean] - true if successful, false otherwise
* value[integer] - new value after the operation or return code if failed.

### memcached:decrement(key, offset [, initial, expiration])
Decrements a key with given offset.

Params:
* offset[integer]
* initial[integer] - optional - initial value if key does not exist.
* expiration[timestamp] - optional - expiration timestamp (integer representation).

Returns:
* ok[boolean] - true if successful, false otherwise
* value[integer] - new value after the operation or return code if failed.

### memcached:increment_by_key(group_key, key, offset [, initial, expiration])
Increments a key with given offset in a group_key.

Params:
* group_key[string]
* key[string]
* offset[integer]
* initial[integer] - optional - initial value if key does not exist.
* expiration[timestamp] - optional - expiration timestamp (integer representation).

Returns:
* ok[boolean] - true if successful, false otherwise
* value[integer] - new value after the operation or return code if failed.

### memcached:increment_by_key(group_key, key, offset [, initial, expiration])
Decrements a key with given offset in a group_key.

Params:
* group_key[string]
* key[string]
* offset[integer]
* initial[integer] - optional - initial value if key does not exist.
* expiration[timestamp] - optional - expiration timestamp (integer representation).

Returns:
* ok[boolean] - true if successful, false otherwise
* value[integer] - new value after the operation or return code if failed.

### memcached:delete(key, expiration)
Deletes a key.

Params:
* key[string] - key to delete
* expiration[integer] - expiration time

Returns:
* ok[boolean] - result status
* rc[integer] - result code

Reference http://docs.libmemcached.org/memcached_delete.html

### memcached:delete_by_key(group_key, key, expiration)
Deletes a key from a group.

Params:
* group_key[string] - key to delete
* key[string] - key to delete
* expiration[integer] - expiration time

Returns:
* ok[boolean] - result status
* rc[integer] - result code

Reference http://docs.libmemcached.org/memcached_delete.html

### memcached:exist(key)
Check if a key exists.

Params:
* key[string]

Returns:
* ok[boolean] - result status (true if key exists, false otherwise)
* rc[integer] - result code

Reference http://docs.libmemcached.org/memcached_exist.html

### memcached:exist_by_key(group_key, key)
Check if a key exists by group_key.

Params:
* group_key[string]
* key[string]

Returns:
* ok[boolean] - result status (true if key exists, false otherwise)
* rc[integer] - result code

Reference http://docs.libmemcached.org/memcached_exist.html

### memcached:flush_buffers()
Flush all buffers by sending buffered commands.

Returns:
* ok[boolean] - result status
* rc[integer] - result code

Reference http://docs.libmemcached.org/memcached_flush_buffers.html

### memcached:flush(expiration)
Flush all buffers by sending buffered commands.

Params:
* expiration[timestamp] - Expiration timestamp (0 - immediate flush!)

Returns:
* ok[boolean] - result status
* rc[integer] - result code

Reference http://docs.libmemcached.org/memcached_flush.html

### memcached:get(key)
Get the value of key from the server.

Params:
* key[any] - will be casted to string!

Returns:
* ok[boolean] - result status
* rc[string/integer] - returns the value (string) or return code
* flags[integer] - flags were stored with the value

Reference http://docs.libmemcached.org/memcached_get.html

### memcached:get_by_key(group_key, key)
Get the value of key from the server.

Params:
* group_key[any] - will be casted to string!
* key[any] - will be casted to string!

Returns:
* ok[boolean] - result status
* rc[string/integer] - returns the value (string) or return code
* flags[integer] - flags were stored with the value

Reference http://docs.libmemcached.org/memcached_get_by_key.html

### memcached:mget(key1, key2, ...)
Get multiple keys vlaues, in order to fetch the results use memcached:fetch_result()

Params:
* key#[any] - will be casted to string!

Returns:
* ok[boolean] - result status
* rc[string/integer] - returns the value (string) or return code

Reference http://docs.libmemcached.org/memcached_get.html#memcached_mget

### memcached:mget_by_key(group_key, key1, key2, ...)
Get multiple keys by group_key, in order to fetch the results use memcached:fetch_result()

Params:
* group_key[any] - will be casted to string!
* key#[any] - will be casted to string!

Returns:
* ok[boolean] - result status
* rc[string/integer] - returns the value (string) or return code

Reference http://docs.libmemcached.org/memcached_get.html#memcached_mget_by_key

### memcached:fetch_result()
Create a result object, should be called after memcached:mget.

Returns:
* ok[boolean] - result status
* result[memcached.result] - result object or error code. See [**result**](result.md) for more information.

Reference http://docs.libmemcached.org/memcached_get.html#memcached_mget

### memcached:set(key, value [, expiration=0, flags=0])
Set value with optional expiration and flags

Params:
* key[string]
* value[string]
* expiration[timestamp] - optional, default: 0 (none)
* flags[integer] - optional, default: 0 (none)

Returns:
* ok[boolean] - result status
* rc[integer] - return code

Reference http://docs.libmemcached.org/memcached_set.html#memcached_set

### memcached:set_by_key(group_key, key, value [, expiration=0, flags=0])
Set value by group_key, with optional expiration and flags

Params:
* group_key[string]
* key[string]
* value[string]
* expiration[timestamp] - optional, default: 0 (none)
* flags[integer] - optional, default: 0 (none)

Returns:
* ok[boolean] - result status
* rc[integer] - return code

Reference http://docs.libmemcached.org/memcached_set.html#memcached_set_by_key

### memcached:add(key, value [, expiration=0, flags=0])
Add a value with optional expiration and flags

Params:
* key[string]
* value[string]
* expiration[timestamp] - optional, default: 0 (none)
* flags[integer] - optional, default: 0 (none)

Returns:
* ok[boolean] - result status
* rc[integer] - return code

Reference http://docs.libmemcached.org/memcached_set.html#memcached_add

### memcached:add_by_key(group_key, key, value [, expiration=0, flags=0])
Add a value by group_key, with optional expiration and flags

Params:
* group_key[string]
* key[string]
* value[string]
* expiration[timestamp] - optional, default: 0 (none)
* flags[integer] - optional, default: 0 (none)

Returns:
* ok[boolean] - result status
* rc[integer] - return code

Reference http://docs.libmemcached.org/memcached_set.html#memcached_add_by_key

### memcached:replace(key, value [, expiration=0, flags=0])
Replace a key value with optional expiration and flags

Params:
* key[string]
* value[string]
* expiration[timestamp] - optional, default: 0 (none)
* flags[integer] - optional, default: 0 (none)

Returns:
* ok[boolean] - result status
* rc[integer] - return code

Reference http://docs.libmemcached.org/memcached_set.html#memcached_replace

### memcached:replace_by_key(group_key, key, value [, expiration=0, flags=0])
Replac a key value by group_key, with optional expiration and flags

Params:
* group_key[string]
* key[string]
* value[string]
* expiration[timestamp] - optional, default: 0 (none)
* flags[integer] - optional, default: 0 (none)

Returns:
* ok[boolean] - result status
* rc[integer] - return code

Reference http://docs.libmemcached.org/memcached_set.html#memcached_replace_by_key

### memcached:prepend(key, value [, expiration=0, flags=0])
Prepend to the value of key with optional expiration and flags

Params:
* key[string]
* value[string]
* expiration[timestamp] - optional, default: 0 (none)
* flags[integer] - optional, default: 0 (none)

Returns:
* ok[boolean] - result status
* rc[integer] - return code

Reference http://docs.libmemcached.org/memcached_append.html#memcached_prepend

### memcached:prepend_by_key(group_key, key, value [, expiration=0, flags=0])
Prepend to the value by group_key, with optional expiration and flags

Params:
* group_key[string]
* key[string]
* value[string]
* expiration[timestamp] - optional, default: 0 (none)
* flags[integer] - optional, default: 0 (none)

Returns:
* ok[boolean] - result status
* rc[integer] - return code

Reference http://docs.libmemcached.org/memcached_append.html#memcached_prepend_by_key

### memcached:append(key, value [, expiration=0, flags=0])
Append to the value of key with optional expiration and flags

Params:
* key[string]
* value[string]
* expiration[timestamp] - optional, default: 0 (none)
* flags[integer] - optional, default: 0 (none)

Returns:
* ok[boolean] - result status
* rc[integer] - return code

Reference http://docs.libmemcached.org/memcached_append.html#memcached_append

### memcached:append_by_key(group_key, key, value [, expiration=0, flags=0])
Append to the value by group_key, with optional expiration and flags

Params:
* group_key[string]
* key[string]
* value[string]
* expiration[timestamp] - optional, default: 0 (none)
* flags[integer] - optional, default: 0 (none)

Returns:
* ok[boolean] - result status
* rc[integer] - return code

Reference http://docs.libmemcached.org/memcached_append.html#memcached_append_by_key

### memcached:cas(key, value [, expiration=0, flags=0, cas=0])
Overwrite the data on the server as long as "cas" is the same.

Params:
* key[string]
* value[string]
* expiration[timestamp] - optional, default: 0 (none)
* flags[integer] - optional, default: 0 (none)
* cas[integer] - optional, default: 0 (none)

Returns:
* ok[boolean] - result status
* rc[integer] - return code

Reference http://docs.libmemcached.org/memcached_cas.html#memcached_cas

### memcached:cas_by_key(group_key, key, value [, expiration=0, flags=0, cas=0])
Overwrite the data on the server as long as "cas" is the same using group_key.

Params:
* group_key[string]
* key[string]
* value[string]
* expiration[timestamp] - optional, default: 0 (none)
* flags[integer] - optional, default: 0 (none)
* cas[integer] - optional, default: 0 (none)

Returns:
* ok[boolean] - result status
* rc[integer] - return code

Reference http://docs.libmemcached.org/memcached_cas.html#memcached_cas_by_key

### memcached:set_encoding_key(encoding_key)
Set the encoding key (currenty only AES is supported).

Params:
* encoding_key[string]

Reference http://docs.libmemcached.org/libmemcached-1.0/memcached_set_encoding_key.html#memcached_set_encoding_key

### memcached:quit()
Disconnect from all connected servers.

Reference http://docs.libmemcached.org/memcached_quit.html

### memcached:behavior_get(flag)
Get behavior by flag.

Params:
* flag[integer] - Select from memcached.BEHAVIOR table

Returns:
* behavior[integer] - Behavior value

Reference http://docs.libmemcached.org/memcached_behavior.html#memcached_behavior_get

### memcached:behavior_set(flag, data)
Set behavior value.

Params:
* flag[integer] - Select from memcached.BEHAVIOR table
* data[integer] - Behavior data to set

Returns:
* ok[booelan]
* rc[integer]

Reference http://docs.libmemcached.org/memcached_behavior.html#memcached_behavior_set

### memcached:generate_hash(key)
Generate a hash based on the memcached instace hash settings.

Params:
* key[string] - Behavior data to set

Returns:
* hash[integer]

Reference http://docs.libmemcached.org/memcached_hash.html#memcached_generate_hash

### memcached.generate_hash_value(key, hash_algorithm)
Generate a hash using a defined algorithm in the library.

Params:
* key[string] - Behavior data to set
* hash_algorith[integer] - Hash algorithm (see memcached.HASH for list of algorithms)

Returns:
* hash[integer]

Reference http://docs.libmemcached.org/memcached_hash.html#memcached_generate_hash_value

### memcached:server_count()
Get the number of current servers used in memcached instance.

Returns:
* count[integer]

Reference http://docs.libmemcached.org/memcached_servers.html#memcached_server_count

### memcached:server_add(host, port)
Add a server

Params:
* host[string]
* port[integer]

Returns:
* ok[booelan] - status
* rc[integer] - return code

Reference http://docs.libmemcached.org/memcached_servers.html#memcached_server_add

### memcached:server_add_udp(host, port)
Add a UDP server

Params:
* host[string]
* port[integer]

Returns:
* ok[booelan] - status
* rc[integer] - return code

Reference http://docs.libmemcached.org/memcached_servers.html#memcached_server_add_udp

### memcached:server_add_unix_socket(socket)
Add a unixsocket based server

Params:
* socket[string]

Returns:
* ok[booelan] - status
* rc[integer] - return code

Reference http://docs.libmemcached.org/memcached_servers.html#memcached_server_add_unix_socket

### memcached:server_by_key()
Get server by key

Returns:
* ok[boolean] - result status
* server[memcached.server] - server object or error code. See [**server**](server.md) for more information.

Reference http://docs.libmemcached.org/memcached_servers.html#memcached_server_by_key

### memcached:touch(key, expiration)
Update key expiration timestamp.

Params:
* key[string]
* expiration[timestamp]

Returns:
* ok[boolean] - result status
* rc[integer] - return code

Reference http://docs.libmemcached.org/memcached_touch.html#memcached_touch

### memcached:touch_by_key(group_key, key, expiration)
Update key expiration by group_key.

Params:
* group_key[string]
* key[string]
* expiration[timestamp]

Returns:
* ok[boolean] - result status
* rc[integer] - return code

Reference http://docs.libmemcached.org/memcached_touch.html#memcached_touch_by_key

### memcached.lib_version()
Returns the libmemcached version.

Returns:
* version[string] - string representation of the libmemcached version.

Reference TODO

### memcached.check_configuration(option_string)
Checks configuration string

Params:
* option_string[string] - Options string.

Returns:
* ok[booelan] - check result.
* error[string] - error message if the check failed.

Reference http://docs.libmemcached.org/libmemcached_configuration.html#libmemcached_check_configuration
