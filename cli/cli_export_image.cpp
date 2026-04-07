#include "backend/backend.hpp"
#include "backend/backend_factory.hpp"
#include "color/apply.hpp"

#include "export/image_export.hpp"

#include <vector>
#include <iostream>

int main () {
  RenderParams params;
  params.width = 15360;
  params.height = 8640;
  params.set = Set::Mandelbrot;
  params.zoom = "1.0";
  params.center_real = "0.0";
  params.center_imag = "0.0";

  IterationParams iteration_params;
  iteration_params.max_iterations = 1000;
  iteration_params.cardioid_check = true;

  Palette palette;
  palette.interpolation_mode = InterpolationMode::Cosine; 
  palette.cycle_length = 100.0;
  palette.colors = {
    RGBA{0,   10,   42, 255},
    RGBA{143,  12, 245, 255},
    RGBA{237, 255, 255, 255},
    RGBA{125, 87, 230,   255},
    RGBA{0,   98,   112,   255},
  };
  palette.interior_color = RGBA{0, 0, 0, 0};

  auto backend = make_backend(Backend::CpuMultiThreaded);
  std::vector<PixelValue> pixels = backend->render_frame(params, iteration_params);
  std::vector<RGBA> colors = apply_palette(palette, pixels, true, iteration_params.max_iterations);

  ImageExportParams export_params;
  export_params.width = 15360;
  export_params.height = 8640;
  export_params.output_path = "test2.png";
  export_params.file_type = ImageFileType::PNG;

  export_image(colors, export_params);

  return 0;
}