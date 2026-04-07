#pragma once

#include "backend.hpp"
#include "core/iterate.hpp"

#include <thread>

class CpuMultiThreaded : public IFractalBackend {
public:
    [[nodiscard]] std::string name() const override { return "CPU Multi Threaded"; }
    [[nodiscard]] std::vector <PixelValue> render_frame(const RenderParams &render_params, const IterationParams &iteration_params) override;

    template<typename SetFunc>
    [[nodiscard]] std::vector <PixelValue> render_with(const SetFunc &set, const RenderParams &render_params, const IterationParams &iteration_params) {
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

        std::vector <PixelValue> buffer(size);

        uint32_t num_threads = std::thread::hardware_concurrency();
        std::vector <std::thread> threads(num_threads);

        for (uint32_t t = 0; t < num_threads; t++) {
            threads[t] = std::thread([&, t]() {
                for (uint32_t y = t; y < render_params.height; y += num_threads) {
                    for (uint32_t x = 0; x < render_params.width; x++) {
                        double real = left + static_cast<double>(x) / static_cast<double>(render_params.width) * vw;
                        double imag = top + static_cast<double>(y) / static_cast<double>(render_params.height) * vh;

                        auto [z, c] = set.make_zc(Complex<double>(real, imag), Complex<double>(c_real, c_imag));
                        buffer[y * render_params.width + x] = iterate(z, c, set, iteration_params);
                    }
                }
            });
        }

        for (auto &thread: threads) {
            thread.join();
        }

        return buffer;
    };
};