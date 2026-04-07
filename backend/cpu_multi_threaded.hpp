#pragma once

#include "backend.hpp"

class CpuMultiThreaded : public IFractalBackend {
public:
    [[nodiscard]] std::string name() const override { return "CPU Multi Threaded"; }
    [[nodiscard]] std::vector<PixelValue> render_frame(const RenderParams& render_params, const IterationParams& iteration_params) override;
};