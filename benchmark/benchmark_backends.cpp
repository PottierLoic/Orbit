#include <benchmark/benchmark.h>

#include "backend/backend_factory.hpp"

class FractalBenchmark : public benchmark::Fixture {
public:
    RenderParams params;
    IterationParams iteration_params;

    // TODO: zoom level and max_iterations change a lot the efficacity of the cardioid check for multi-threaded backend
    //       should find a configuration that gives more significant results
    void SetUp(const benchmark::State&) override {
        params.width = 3840;
        params.height = 2160;
        params.set = Set::Mandelbrot;
        params.zoom = "1.0";
        params.center_real = "0.0";
        params.center_imag = "0.0";
        iteration_params.max_iterations = 1000;
    }
};

BENCHMARK_F(FractalBenchmark, CpuSingleThreaded_NoCheck)(benchmark::State& state) {
    auto backend = make_backend(Backend::CpuSingleThreaded);
    iteration_params.cardioid_check = false;
    for (auto _ : state) {
        auto pixels = backend->render_frame(params, iteration_params);
        benchmark::DoNotOptimize(pixels);
    }

    state.counters["pixels/sec"] = benchmark::Counter(
    static_cast<double>(params.width) * params.height * state.iterations(),
        benchmark::Counter::kIsRate
    );
}

BENCHMARK_F(FractalBenchmark, CpuSingleThreaded_CardioidCheck)(benchmark::State& state) {
    auto backend = make_backend(Backend::CpuSingleThreaded);
    iteration_params.cardioid_check = true;
    for (auto _ : state) {
        auto pixels = backend->render_frame(params, iteration_params);
        benchmark::DoNotOptimize(pixels);
    }

    state.counters["pixels/sec"] = benchmark::Counter(
    static_cast<double>(params.width) * params.height * state.iterations(),
        benchmark::Counter::kIsRate
    );
}

BENCHMARK_F(FractalBenchmark, CpuMultiThreaded_NoCheck)(benchmark::State& state) {
    auto backend = make_backend(Backend::CpuMultiThreaded);
    iteration_params.cardioid_check = false;
    for (auto _ : state) {
        auto pixels = backend->render_frame(params, iteration_params);
        benchmark::DoNotOptimize(pixels);
    }

    state.counters["pixels/sec"] = benchmark::Counter(
    static_cast<double>(params.width) * params.height * state.iterations(),
        benchmark::Counter::kIsRate
    );
}

BENCHMARK_F(FractalBenchmark, CpuMultiThreaded_CardioidCheck)(benchmark::State& state) {
    auto backend = make_backend(Backend::CpuMultiThreaded);
    iteration_params.cardioid_check = true;
    for (auto _ : state) {
        auto pixels = backend->render_frame(params, iteration_params);
        benchmark::DoNotOptimize(pixels);
    }

    state.counters["pixels/sec"] = benchmark::Counter(
    static_cast<double>(params.width) * params.height * state.iterations(),
        benchmark::Counter::kIsRate
    );
}

int main(int argc, char** argv) {
    benchmark::Initialize(&argc, argv);
    benchmark::SetDefaultTimeUnit(benchmark::kMillisecond);
    benchmark::RunSpecifiedBenchmarks();
    benchmark::Shutdown();
    return 0;
}