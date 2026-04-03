#include "cpu_single_threaded.hpp"

#include "core/sets/mandelbrot.hpp"
#include "core/sets/julia.hpp"
#include "core/iterate.hpp"
#include <vector>

template <typename SetFunc>
std::vector<PixelValue> render_with(const SetFunc& set, const RenderParams& render_params, const IterationParams& iteration_params) {
    double center_real = std::stod(render_params.center_real);
    double center_imag = std::stod(render_params.center_imag);

    double c_real = std::stod(render_params.c_real);
    double c_imag = std::stod(render_params.c_imag);

    double zoom = std::stod(render_params.zoom);

    double aspect = static_cast<double>(render_params.width) / static_cast<double>(render_params.height);
    double vw = 3.5 / zoom;
    double vh = vw / aspect;
    double left = center_real - vw / 2.0;
    double top = center_imag - vh / 2.0;
    size_t size = render_params.width * render_params.height;

    std::vector<PixelValue> buffer(size);

    for (size_t i = 0; i < size; i++) {
        int x = i % render_params.width;
        int y = i / render_params.width;

        double real = left + static_cast<double>(x) / static_cast<double>(render_params.width) * vw;
        double imag = top + static_cast<double>(y) / static_cast<double>(render_params.height) * vh;

        auto [z, c] = set.make_zc(Complex<double>(real, imag), Complex<double>(c_real, c_imag));

        buffer[i] = iterate(z, c, set, iteration_params);
    }

    return buffer;
}

std::vector<PixelValue> CpuSingleThreaded::render_frame(const RenderParams& render_params, const IterationParams& iteration_params) {
    switch (render_params.set) {
        case Set::Mandelbrot: return render_with(MandelbrotSet<double>{}, render_params, iteration_params);
        case Set::Julia: return render_with(JuliaSet<double>{}, render_params, iteration_params);
        default: throw std::runtime_error("Unknown Set");
    }
}