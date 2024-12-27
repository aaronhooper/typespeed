# typespeed

A game where you type words to remove them from the screen and score points.

## Intention

This is less about the game itself and more about being an opportunity for me to explore the raylib library and different memory management strategies.

## Dependencies

- CMake >=3.14

Only tested on macOS 14 (AArch64). Will need some tweaking to work on other systems.

## Building

```bash
cmake -B build
cmake --build build
```

## Running

```bash
build/typespeed
```

## Testing

```bash
build/tests
# -- OR --
cd build
ctest
```

