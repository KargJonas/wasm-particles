# wasm-particles

[![Netlify Status](https://api.netlify.com/api/v1/badges/36915f03-5e34-4a97-a485-d4f482f6b4a5/deploy-status)](https://app.netlify.com/sites/wasm-particles/deploys)

This is just a little demo project vor WebAssembly. The "simulation" imitates electromagnetic attraction and repulsion between two types of differently charged particles. Additionally, there is friction and primitive collision detection.

In order to build this, you will need [emscripten](https://emscripten.org/docs/getting_started/downloads.html).

| Command    | Usage                          |
| ---------- | ------------------------------ |
| make main  | Compile to WASM binary         |
| make clean | Delete build directory         |
| make serve | Serve the project on port 5500 |

![Example](example.png)