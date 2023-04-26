# Cpp-Hashmap
A basic Hashmap class for C++.

###Member functions
`insert(Key key, Value value)` : Inserts a key-value pair into the hashmap.
`erase(Key key)` : Erases a key-value pair from the hashmap. If the given key is found, it returns `true`, else `false`.
`clear(Key key)` : Clears the contents of the hashmap.
`operator[](Key key)` : Returns a reference to the Value associated with the Key provided as an argument. If the key is not found, it will return a reference to a value-initialised variable of type `Value`.

The user can optionally provide a pointer to a hash function in the constructor. The return type must be of type `size_t`, and there must be a single argument of the template type `Key`.