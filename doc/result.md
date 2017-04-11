### memcached.result

### result:key()
Get the key value of the result

Returns:
* key[string]

Reference http://docs.libmemcached.org/memcached_result_st.html

### result:value()
Get the value

Returns:
* value[string]

Reference http://docs.libmemcached.org/memcached_result_st.html

### result:flags()
Get the flags

Returns:
* flags[integer]

Reference http://docs.libmemcached.org/memcached_result_st.html#memcached_result_flags

### result:cas()
Get the cas

Returns:
* cas[integer]

Reference http://docs.libmemcached.org/memcached_result_st.html#memcached_result_cas

### result:set_value(new_value)
Set result value

Params:
* new_value[string]

Returns:
* ok[booelan]
* rc[integer]

Reference http://docs.libmemcached.org/memcached_result_st.html#memcached_result_set_value

### result:set_flags(new_flags)
Set result flags

Params:
* new_flags[integer]

Reference http://docs.libmemcached.org/memcached_result_st.html#memcached_result_set_flags

### result:set_expiration(new_expiration)
Set result expiration

Params:
* new_expiration[integer]

Reference http://docs.libmemcached.org/memcached_result_st.html#memcached_result_set_expiration
