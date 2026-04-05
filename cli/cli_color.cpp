#include "backend/backend.hpp"
#include "backend/backend_factory.hpp"
#include "color/apply.hpp"

#include <vector>
#include <iostream>

int main () {
  RenderParams params;
  params.width = 100;
  params.height = 40;
  params.set = Set::Mandelbrot;
  params.zoom = "0.5";
  params.center_real = "0.0";
  params.center_imag = "0.0";

  IterationParams iteration_params;
  iteration_params.max_iterations = 100;
  iteration_params.cardioid_check = true;

  Palette palette;
  palette.interpolation_mode = InterpolationMode::Linear; 
  palette.cycle_length = 32.0;
  palette.colors = {
    RGBA{0,   7,   100, 255},
    RGBA{32,  107, 203, 255},
    RGBA{237, 255, 255, 255},
    RGBA{255, 170, 0,   255},
    RGBA{0,   2,   0,   255},
  };

  auto backend = make_backend(Backend::CpuSingleThreaded);
  std::vector<PixelValue> pixels = backend->render_frame(params, iteration_params);
  std::vector<RGBA> colors = apply_palette(palette, pixels, false);

  const char* chars = " .-:;+=xX$&@#";
  size_t num_chars = 13;

  for (size_t i = 0; i < colors.size(); i++) {
    uint8_t brightness = (colors[i].r + colors[i].g + colors[i].b) / 3;
    size_t char_idx = (brightness * num_chars) / 256;
    std::cout << chars[char_idx];
    if (i % params.width == params.width - 1) std::cout << "\n";
  }

  return 0;
}