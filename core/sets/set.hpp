#pragma once

enum class Set {
    Mandelbrot,
    Julia,
    BurningShip,
};

inline const char* set_names[] = { "Mandelbrot", "Julia", "Burning Ship"};
constexpr size_t set_count = 3;