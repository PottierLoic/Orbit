#include "cpu_single_threaded.hpp"

#include "core/sets/mandelbrot.hpp"
#include "core/sets/julia.hpp"
#include <vector>

std::vector<PixelValue> CpuSingleThreaded::render_frame(const RenderParams& render_params, const IterationParams& iteration_params, IFractalBackend::ProgressCallback on_progress) {
    switch (render_params.set) {
        case Set::Mandelbrot: return render_with(MandelbrotSet<double>{}, render_params, iteration_params, on_progress);
        case Set::Julia: return render_with(JuliaSet<double>{}, render_params, iteration_params, on_progress);
        default: throw std::runtime_error("Unknown Set");
    }
}