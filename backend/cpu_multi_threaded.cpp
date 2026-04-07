#include "cpu_multi_threaded.hpp"

#include "core/sets/mandelbrot.hpp"
#include "core/sets/julia.hpp"

[[nodiscard]] std::vector<PixelValue> CpuMultiThreaded::render_frame(const RenderParams& render_params, const IterationParams& iteration_params) {
    switch (render_params.set) {
        case Set::Mandelbrot: return render_with(MandelbrotSet<double>{}, render_params, iteration_params);
        case Set::Julia: return render_with(JuliaSet<double>{}, render_params, iteration_params);
        default: throw std::runtime_error("Unknown Set");
    }
}
