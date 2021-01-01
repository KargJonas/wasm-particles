# wasm-particles

This is just a little demo project vor WebAssembly. The "simulation" imitates electromagnetic attraction and repulsion between two types of differently charged particles. Additionally, there is friction and primitive collision detection.

In order to build this, you will need [emscripten](https://emscripten.org/docs/getting_started/downloads.html).

| Command    | Usage                          |
| ---------- | ------------------------------ |
| make main  | Compile to WASM binary         |
| make clean | Delete build directory         |
| make serve | Serve the project on port 5500 |

![Example](example.png)