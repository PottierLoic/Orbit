#include <doctest/doctest.h>

#include "color/rgba.hpp"
#include "color/interpolation_mode.hpp"
#include "color/interpolation.hpp"
#include "core/pixel_value.hpp"

TEST_CASE("interpolate_linear return correct value") {
    Palette palette;
    palette.interpolation_mode = InterpolationMode::Linear;
    palette.colors = {RGBA{0, 0, 0, 255}, RGBA{100, 100, 100, 255}};
    palette.cycle_length = 20;

    RGBA color = interpolate_linear(palette, 10);
    CHECK(color.r == 50);
    CHECK(color.g == 50);
    CHECK(color.b == 50);
    CHECK(color.a == 255);
}

TEST_CASE("interpolate_cosine return correct value") {
    Palette palette;
    palette.interpolation_mode = InterpolationMode::Cosine;
    palette.colors = {RGBA{0, 0, 0, 255}, RGBA{100, 100, 100, 255}};
    palette.cycle_length = 20;

    RGBA color = interpolate_cosine(palette, 5);
    CHECK(color.r == 14);
    CHECK(color.g == 14);
    CHECK(color.b == 14);
    CHECK(color.a == 255);
}

TEST_CASE("interpolate_none return correct value") {
    Palette palette;
    palette.interpolation_mode = InterpolationMode::None;
    palette.colors = {RGBA{0, 0, 0, 255}, RGBA{100, 100, 100, 255}};
    palette.cycle_length = 20;

    RGBA color = interpolate_none(palette, 1);
    CHECK(color.r == 100);
    CHECK(color.g == 100);
    CHECK(color.b == 100);
    CHECK(color.a == 255);
}

TEST_CASE("1-color palette always return its only color") {
    Palette palette;
    palette.interpolation_mode = InterpolationMode::None;
    palette.colors = {RGBA{13, 13, 13, 255}};
    palette.cycle_length = 20;

    RGBA color = interpolate_none(palette, 1);
    CHECK(color.r == 13);
    CHECK(color.g == 13);
    CHECK(color.b == 13);
    CHECK(color.a == 255);
}

TEST_CASE("Looping paltte multiple times is working as expected") {
    Palette palette;
    palette.interpolation_mode = InterpolationMode::None;
    palette.colors = {RGBA{0, 0, 0, 255}, RGBA{100, 100, 100, 255}, RGBA{150, 150, 150, 255}};
    palette.cycle_length = 3;

    RGBA color = interpolate_none(palette, 92);
    CHECK(color.r == 150);
    CHECK(color.g == 150);
    CHECK(color.b == 150);
    CHECK(color.a == 255);
}
