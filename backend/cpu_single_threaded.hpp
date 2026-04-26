#pragma once

#include "backend.hpp"
#include "helper.hpp"
#include "core/iterate.hpp"

class CpuSingleThreaded : public IFractalBackend {
public:
    [[nodiscard]] std::string name() const override { return "CPU Single Threaded"; }
    [[nodiscard]] std::vector <PixelValue> render_frame(const RenderParams &render_params, const IterationParams &iteration_params, IFractalBackend::ProgressCallback on_progress) override;

    template<typename SetFunc>
    [[nodiscard]] std::vector <PixelValue> render_with(const SetFunc &set, const RenderParams &render_params, const IterationParams &iteration_params, IFractalBackend::ProgressCallback on_progress) {
        double center_real = safe_stod(render_params.center_real);
        double center_imag = safe_stod(render_params.center_imag);

        double c_real = safe_stod(render_params.c_real);
        double c_imag = safe_stod(render_params.c_imag);

        double zoom = safe_stod(render_params.zoom);

        double aspect = static_cast<double>(render_params.width) / static_cast<double>(render_params.height);
        double vw = 3.5 / zoom;
        double vh = vw / aspect;
        double left = center_real - vw / 2.0;
        double top = center_imag - vh / 2.0;
        size_t size = render_params.width * render_params.height;

        std::vector <PixelValue> buffer(size);

        int last_y = 0;
        for (size_t i = 0; i < size; i++) {
            int x = i % render_params.width;
            int y = i / render_params.width;

            double real = left + static_cast<double>(x) / static_cast<double>(render_params.width) * vw;
            double imag = top + static_cast<double>(y) / static_cast<double>(render_params.height) * vh;

            auto [z, c] = set.make_zc(Complex<double>(real, imag), Complex<double>(c_real, c_imag));

            buffer[i] = iterate(z, c, set, iteration_params);

            if (on_progress && y != last_y) {
                if (!on_progress()) { break; }
                last_y = y;
            }

        }

        return buffer;
    };
};