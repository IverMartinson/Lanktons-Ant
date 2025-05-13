# Lanktons-Ant
### The Lankton's Ant program written in C 
#### How to run
1. Download the binary or compile from source
2. Run it in the CMD line or from a file browser (if you're in the CMD line you can use `--randomize` to randomize the cells or `--trace` to trace the ant's path)

#### How to compile
1. Download SDL2 (libsdl2-dev from apt)
2. Compile with any C compiler

#### Example compiler command
`gcc main.c -o main -lc -lSDL2 -Ofast`
- gcc: the GCC compiler
- main.c: input file
- -o main: call the binary "main"
- -lc: link the C library
- -lSDL2: link the SDL2 library
- -Ofast: use the fastest optimizations

#### What should I edit in the source?
- Window dimensions
- The frames skipped (creates the illusion of speed. More frames skipped, faster it goes. Another way to think about it would be the number of substeps before rendering)
- The ant's rules
