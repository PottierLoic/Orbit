#include <doctest/doctest.h>
#include "iterate.hpp"
#include "sets/mandelbrot.hpp"

struct AlwaysEscape {
    Complex<double> operator()(const Complex<double>& z, const Complex<double>& c) const {
        return z + c + Complex<double>(10.0, 10.0);
    }
};

struct NeverEscape {
    Complex<double> operator()(const Complex<double>&, const Complex<double>&) const {
        return Complex<double>(0.0, 0.0);
    }
};

TEST_CASE("iterate: escapes before max_iterations") {
    IterationParams params;
    params.max_iterations = 100;

    AlwaysEscape f;
    auto result = iterate(Complex<double>(0.0, 0.0), Complex<double>(0.0, 0.0), f, params);
    CHECK(result.iterations < params.max_iterations);
}

TEST_CASE("iterate: reaches max_iterations when bounded") {
    IterationParams params;
    params.max_iterations = 50;

    NeverEscape f;
    auto result = iterate(Complex<double>(0.0, 0.0), Complex<double>(0.0, 0.0), f, params);
    CHECK(result.iterations == params.max_iterations);
}

TEST_CASE("iterate: returns final_z at escape") {
    IterationParams params;
    params.max_iterations = 100;

    AlwaysEscape f;
    auto result = iterate(Complex<double>(0.0, 0.0), Complex<double>(0.0, 0.0), f, params);
    CHECK(result.final_z.squared_norm() >= 4.0);
}

TEST_CASE("iterate: func with no cardioid_check ignores cardioid_check flag") {
    IterationParams params;
    params.max_iterations = 50;
    params.cardioid_check = true;

    NeverEscape f;
    // NeverEscape has no cardioid_check member — should compile and run normally
    auto result = iterate(Complex<double>(0.0, 0.0), Complex<double>(0.0, 0.0), f, params);
    CHECK(result.iterations == params.max_iterations);
}

TEST_CASE("iterate: max_iterations of 0 returns immediately") {
    IterationParams params;
    params.max_iterations = 0;

    MandelbrotSet<double> f;
    auto result = iterate(Complex<double>(0.0, 0.0), Complex<double>(0.0, 0.0), f, params);
    CHECK(result.iterations == 0);
}

TEST_CASE("iterate: works with float precision") {
    IterationParams params;
    params.max_iterations = 100;

    MandelbrotSet<float> f;
    auto result = iterate(Complex<float>(0.0f, 0.0f), Complex<float>(2.0f, 2.0f), f, params);
    CHECK(result.iterations < params.max_iterations);
}