#pragma once

#include <cstdint>

#include "complex.hpp"

template <typename T>
struct PixelValue {
    uint32_t iterations = 0;
    Complex<T> final_z = Complex<T>(0, 0);
};