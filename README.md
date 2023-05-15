# Malloc-ky
spicy implementation of malloc() with garbage collection 

`make` then `./heap`

## Makefile (flags explanation)
- Wall: enables all warning messages that the compiler can produce. This helps to catch potential issues in the code that may cause problems at runtime.

- Wextra: enables even more warning messages that are not enabled by -Wall. This helps to catch additional potential issues that may have been missed by Wall.

- pedantic: causes the compiler to issue warnings for any code that does not conform to the C standard. This helps to ensure that the code is written in a portable manner and can be compiled by any C compiler.

- ggdb: adds debugging information to the compiled binary that can be used by the gdb debugger. This includes information about source code lines and symbols, which can be helpful when debugging the program.

### Problems I ran into:

- [ ] when `heap_alloc(0)` and `heap_alloc(1)` are called simaltaneously they have the same pointer address. Handle size 0? sol: I just skilled when 0 is called returning Null

```
Alloced Chunks (101): 
 start: 0x5638574da040, size: 0
 start: 0x5638574da040, size: 1
```

- when freeing chunks a hashtable would be better to have pointer as key and address as chunk?

Final
- Insert, Remove are O(n) lookup is O(log n)
