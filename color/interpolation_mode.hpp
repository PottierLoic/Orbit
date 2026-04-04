#pragma once

enum class InterpolationMode {
    Linear,
    Cosine,
    HSV,
    HSVCyclic,
};

struct PaletteIndices {
    size_t idx_a;
    size_t idx_b;
    double local_t;
};