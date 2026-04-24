#pragma once

#include <vector>
#include <string>

#include "rgba.hpp"
#include "interpolation_mode.hpp"

struct Palette {
    InterpolationMode interpolation_mode;
    std::vector<RGBA> colors;
    RGBA interior_color;
    double cycle_length;
    std::string name;
};
