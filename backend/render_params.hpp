#pragma once

#include <string>
#include <cstdint>

#include "core/sets/set.hpp"

struct RenderParams {
    uint32_t width = 800;
    uint32_t height = 600;

    Set set = Set::Mandelbrot;

    std::string center_real = "0.0";
    std::string center_imag = "0.0";
    std::string zoom = "1.0";

    std::string c_real = "-0.7";
    std::string c_imag = "0.27";
};