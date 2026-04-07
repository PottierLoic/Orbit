#include "backend/backend.hpp"
#include "backend/backend_factory.hpp"
#include "color/apply.hpp"

#include "export/image_export.hpp"

#include <vector>
#include <iostream>

int main () {
  RenderParams params;
  params.width = 100;
  params.height = 100;
  params.set = Set::Mandelbrot;
  params.zoom = "0.5";
  params.center_real = "0.0";
  params.center_imag = "0.0";

  IterationParams iteration_params;
  iteration_params.max_iterations = 100;
  iteration_params.cardioid_check = true;

  Palette palette;
  palette.interpolation_mode = InterpolationMode::Cosine; 
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
  std::vector<RGBA> colors = apply_palette(palette, pixels, true, iteration_params.max_iterations);

  ExportParams export_params;
  export_params.width = 100;
  export_params.height = 100;
  export_params.output_path = "test2.png";
  export_params.file_type = FileType::PNG;

  export_png(colors, export_params);

  return 0;
}