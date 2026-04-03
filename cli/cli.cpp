#include "backend/backend.hpp"
#include "backend/backend_factory.hpp"

#include <vector>
#include <iostream>

int main () {
  RenderParams params;
  params.width = 100;
  params.height = 40;
  params.set = Set::Julia;
  params.zoom = "0.5";
  params.center_real = "0.0";
  params.center_imag = "0.0";

  params.c_real = "-0.7";
  params.c_imag = "0.27";

  IterationParams iteration_params;
  iteration_params.max_iterations = 100;
  iteration_params.cardioid_check = false;

  auto backend = make_backend(Backend::CpuSingleThreaded);

  std::vector<PixelValue> pixels = backend->render_frame(params, iteration_params);

  std::cout << "pixels size: " << pixels.size() << "\n";
  for (size_t i = 0; i < pixels.size(); i++) {
    if (pixels[i].iterations == iteration_params.max_iterations) {
      std::cout << "#";
    } else {
      std::cout << "@";
    }
    if (i % params.width == params.width - 1) std::cout << "\n";
  }

  return 0;
}