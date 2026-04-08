#pragma once

#include <vector>
#include <cmath>

#include "rgba.hpp"
#include "palette.hpp"
#include "interpolation.hpp"
#include "core/pixel_value.hpp"

[[nodiscard]] inline double pixel_to_double(const PixelValue& pixel, bool smooth) {
    if (smooth) {
        double log_zn = std::log2(pixel.final_z.norm());
        return static_cast<double>(pixel.iterations) - std::log2(log_zn);
    }
    return static_cast<double>(pixel.iterations);
}

[[nodiscard]] std::vector<RGBA> apply_palette(const Palette& palette, const std::vector<PixelValue>& pixels, bool smooth, uint32_t max_iterations);