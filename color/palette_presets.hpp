#pragma once

#include "palette.hpp"

inline const Palette palette_default = {
        InterpolationMode::Linear,
        {
                RGBA{0,   7,   100, 255},
                RGBA{32,  107, 203, 255},
                RGBA{237, 255, 255, 255},
                RGBA{255, 170, 0,   255},
                RGBA{0,   2,   0,   255},
        },
        RGBA{0, 0, 0, 255},
        32.0,
        "Default"
};

inline const Palette palette_rainbow = {
        InterpolationMode::Linear,
        {
                RGBA{255, 0,   0,   255},
                RGBA{255, 165, 0,   255},
                RGBA{255, 255, 0,   255},
                RGBA{0,   255, 0,   255},
                RGBA{0,   0,   255, 255},
                RGBA{148, 0,   211, 255},
        },
        RGBA{0, 0, 0, 255},
        64.0,
        "Rainbow"
};

inline const Palette palette_fire = {
        InterpolationMode::Cosine,
        {
                RGBA{0,   0,   0,   255},
                RGBA{180, 0,   0,   255},
                RGBA{255, 80,  0,   255},
                RGBA{255, 200, 0,   255},
                RGBA{255, 255, 200, 255},
        },
        RGBA{0, 0, 0, 255},
        48.0,
        "Fire"
};

inline const Palette palette_ice = {
        InterpolationMode::Cosine,
        {
                RGBA{0,   0,   30,  255},
                RGBA{0,   60,  130, 255},
                RGBA{100, 180, 255, 255},
                RGBA{200, 230, 255, 255},
                RGBA{255, 255, 255, 255},
        },
        RGBA{0, 0, 20, 255},
        40.0,
        "Ice"
};

inline const Palette palette_forest = {
        InterpolationMode::Linear,
        {
                RGBA{0,   20,  0,   255},
                RGBA{10,  80,  10,  255},
                RGBA{50,  150, 30,  255},
                RGBA{180, 220, 80,  255},
                RGBA{230, 240, 180, 255},
        },
        RGBA{0, 10, 0, 255},
        48.0,
        "Forest"
};

inline const Palette palette_ocean = {
        InterpolationMode::Cosine,
        {
                RGBA{0,   5,   40,  255},
                RGBA{0,   40,  100, 255},
                RGBA{0,   100, 180, 255},
                RGBA{0,   180, 200, 255},
                RGBA{180, 230, 240, 255},
        },
        RGBA{0, 2, 20, 255},
        56.0,
        "Ocean"
};

inline const Palette palette_plasma = {
        InterpolationMode::Cosine,
        {
                RGBA{13,  8,   135, 255},
                RGBA{126, 3,   167, 255},
                RGBA{204, 71,  120, 255},
                RGBA{248, 149, 64,  255},
                RGBA{240, 249, 33,  255},
        },
        RGBA{0, 0, 0, 255},
        48.0,
        "Plasma"
};

inline const Palette palette_fire_ice = {
        InterpolationMode::Cosine,
        {
                RGBA{0,   0,   180, 255},
                RGBA{100, 180, 255, 255},
                RGBA{255, 255, 255, 255},
                RGBA{255, 150, 0,   255},
                RGBA{180, 0,   0,   255},
        },
        RGBA{0, 0, 0, 255},
        64.0,
        "Fire & Ice"
};

inline std::vector<Palette>& get_all_palettes() {
        static std::vector<Palette> palettes = {
                palette_default, palette_rainbow, palette_fire, palette_ice,
                palette_forest, palette_ocean, palette_plasma, palette_fire_ice
        };
        return palettes;
}