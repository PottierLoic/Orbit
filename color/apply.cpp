#include "apply.hpp"

[[nodiscard]] std::vector<RGBA> apply_palette(const Palette& palette, const std::vector<PixelValue>& pixels, bool smooth, uint32_t max_iterations) {
    std::vector<RGBA> result;
    result.reserve(pixels.size());

    RGBA (*interpolation_function)(const Palette&, double t) = nullptr;

    switch(palette.interpolation_mode) {
        case InterpolationMode::Linear : interpolation_function = interpolate_linear; break;
        case InterpolationMode::Cosine : interpolation_function = interpolate_cosine; break;
        default: interpolation_function = interpolate_none; break;
    }

    for (const auto& pixel: pixels) {
    if (pixel.iterations == max_iterations) {
        result.push_back(palette.interior_color);
        continue;
    }
        double t = pixel_to_double(pixel, smooth);
        result.push_back(interpolation_function(palette, t));
    }

    return result;
}