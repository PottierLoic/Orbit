#include <doctest/doctest.h>

#include "color/apply.hpp"
#include "color/palette.hpp"
#include "core/pixel_value.hpp"
#include "core/complex.hpp"

TEST_CASE("RGBA vector size is equal to PixelValue vector size") {
    std::vector<PixelValue> pixels = {PixelValue{1, Complex<double>(0, 0)}, PixelValue{1, Complex<double>(0, 0)}};
    Palette palette;
    palette.colors = {RGBA{0, 0, 0, 255}};
    palette.cycle_length = 1;
    std::vector<RGBA> colors = apply_palette(palette, pixels, false, 100);
    CHECK(pixels.size() == colors.size());
}