#pragma once

#include <stdexcept>
#include <memory>

#include "backend.hpp"
#include "cpu_single_threaded.hpp"
#include "cpu_multi_threaded.hpp"

std::unique_ptr<IFractalBackend> make_backend(Backend backend) {
    switch(backend) {
        case Backend::CpuSingleThreaded: return std::make_unique<CpuSingleThreaded>();
        case Backend::CpuMultiThreaded: return std::make_unique<CpuMultiThreaded>();
//        case Backend::CpuTiled: return std::make_unique<xxx>();
//        case Backend::Gpu: return std::make_unique<xxx>();
//        case Backend::CpuArbitraryPrecision: return std::make_unique<xxx>();
        default: throw std::runtime_error("Unknown backend");
    }
}