# spinny cube

spinny cube

![c64cube running ih VICE (C64SC)](assets/cube.png)

## how 2 build
you need the [LLVM-MOS SDK](https://github.com/llvm-mos/llvm-mos-sdk) to build c64cube.

once you extracted it somewhere, invoke CMake like so:
```sh
cmake .. -DCMAKE_PREFIX_PATH=$HOME/.local/llvm-mos
```

CMake might complain that it couldn't find a make program. if that is the case, add `-DCMAKE_MAKE_PROGRAM=$(which make)` to your CMake arguments.

now run `make -j$(nproc)`, then load the `c64cube.prg` program file into an emulator of choice
