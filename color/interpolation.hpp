#pragma once

#include <cmath>
#include <cstdint>

#include "palette.hpp"
#include "rgba.hpp"
#include "interpolation_mode.hpp"

[[nodiscard]] PaletteIndices get_palette_indices(const Palette& palette, double t) {
    double scaled_t = t / palette.cycle_length;

    uint32_t size = palette.colors.size();
    if (size == 0) {
        return PaletteIndices{0, 0, 0.0};
    } else if (size == 1) {
        return PaletteIndices{0, 0, 1.0};
    } else {
        double scaled = scaled_t * size;
        double local_t = scaled - std::floor(scaled);
        size_t idx_a = static_cast<size_t>(std::floor(scaled));
        size_t idx_b = (idx_a + 1) % size;
        return PaletteIndices{idx_a, idx_b, local_t};
    }
}

[[nodiscard]] RGBA interpolate_linear(const Palette& palette, double t) {
    PaletteIndices indices = get_palette_indices(palette, t);
    RGBA color_a = palette.colors[indices.idx_a];
    RGBA color_b = palette.colors[indices.idx_b];

    uint8_t r = static_cast<uint8_t>(color_a.r + indices.local_t * (static_cast<int>(color_b.r) - static_cast<int>(color_a.r)));
    uint8_t g = static_cast<uint8_t>(color_a.g + indices.local_t * (static_cast<int>(color_b.g) - static_cast<int>(color_a.g)));
    uint8_t b =  static_cast<uint8_t>(color_a.b + indices.local_t * (static_cast<int>(color_b.b) - static_cast<int>(color_a.b)));

    return RGBA{r, g, b, 255};
}
