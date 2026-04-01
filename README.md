# Orbit

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)


Orbit is a high-performance fractal renderer written in C++.
It features multiple compute backends, multithreaded tile rendering, and supports both interactive exploration and high-resolution image/video export.

## Features
- Interactive exploration
- Video recording via FFmpeg
- High-resolution image export
- Customizable color palettes
- Multiple compute backends (CPU, GPU, arbitrary precision)
- Multithreaded tile rendering


## Getting started

### Dependencies
- CMake 3.21+, Ninja
- C++20 compiler
- FFmpeg (required for video export)
- GLFW, Dear ImGui (required for gui)
- **NOT YET** - MPFR (for arbitrary precision backend)
- **NOT YET** - CUDA or OpenCL (for gpu backend)

```bash
cmake -G Ninja -B build
cmake --build build
```

## Architecture

Orbit is split into independent modules with a strict separation of concerns:

- core: pure maths such as complex numbers, iteration, smooth coloring, palettes. 
- backend: compute strategies that orchestrate core: single-threaded CPU, tiled multithreaded CPU, GPU.
- render: combines the backend and palettes to produce a pixel buffer ready for display and / or export.
- gui: Interactive viewer built with GLFW and Dear ImGui.
- cli: command-line interface for headless image and video rendering.

## Roadmap & Contributing

Contributions are welcome, there is a lot of ground to cover.
The current roadmap and task board are tracked in the [GitHub project](https://github.com/users/PottierLoic/projects/3/views/1?filterQuery=).

## Museum

Some really cool images can be seen in the `museum` folder.
