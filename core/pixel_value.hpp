#pragma once

#include <cstdint>

#include "complex.hpp"

struct PixelValue {
    uint32_t iterations = 0;
    Complex<double> final_z = Complex<double>(0, 0);
};