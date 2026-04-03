#pragma once

#include <vector>
#include <string>
#include <memory>

#include "render_params.hpp"
#include "core/iteration_params.hpp"
#include "core/pixel_value.hpp"

enum class Backend {
    CpuSingleThreaded,
    CpuMultiThreaded,
    CpuTiled,
    Gpu,
    CpuArbitraryPrecision
};

class IFractalBackend {
public:
    virtual ~IFractalBackend() = default;
    [[nodiscard]] virtual std::vector<PixelValue> render_frame(const RenderParams& render_params, const IterationParams& iteration_params) = 0;
    [[nodiscard]] virtual std::string name() const = 0;
};
