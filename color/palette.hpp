#pragma once

#include <vector>

#include "rgba.hpp"
#include "interpolation_mode.hpp"

struct Palette {
    InterpolationMode interpolation_mode;
    std::vector<RGBA> colors;
    double cycle_length;
};
