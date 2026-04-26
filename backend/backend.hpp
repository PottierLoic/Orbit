#pragma once

#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <cstdint>

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
inline const char* backend_names[] = { "CPU Single Threaded", "CPU Multi Threaded", "CPU Tiled", "GPU", "CPU Arbitrary Precision"};
constexpr size_t backend_count = 5;

class IFractalBackend {
public:
    using ProgressCallback = std::function<bool()>;

    virtual ~IFractalBackend() = default;
    [[nodiscard]] virtual std::vector<PixelValue> render_frame(const RenderParams& render_params, const IterationParams& iteration_params, ProgressCallback on_progress = nullptr) = 0;
    [[nodiscard]] virtual std::string name() const = 0;
};
