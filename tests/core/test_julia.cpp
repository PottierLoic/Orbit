#include <doctest/doctest.h>
#include "sets/julia.hpp"
#include "iterate.hpp"

TEST_CASE("JuliaSet: iteration formula z^2+c") {
    JuliaSet<double> f;
    // z=1+1i, c=0+0i => z^2+c = 0+2i
    auto result = f(Complex<double>(1.0, 1.0), Complex<double>(0.0, 0.0));
    CHECK(result.real() == doctest::Approx(0.0));
    CHECK(result.imag() == doctest::Approx(2.0));
}

TEST_CASE("JuliaSet: c is added to z^2") {
    JuliaSet<double> f;
    // z=1+0i, c=2+3i => z^2+c = 1+0i + 2+3i = 3+3i
    auto result = f(Complex<double>(1.0, 0.0), Complex<double>(2.0, 3.0));
    CHECK(result.real() == doctest::Approx(3.0));
    CHECK(result.imag() == doctest::Approx(3.0));
}

TEST_CASE("JuliaSet: works with float") {
    JuliaSet<float> f;
    // z=1+0i, c=1+0i => z^2+c = 1+0i + 1+0i = 2+0i
    auto result = f(Complex<float>(1.0f, 0.0f), Complex<float>(1.0f, 0.0f));
    CHECK(result.real() == doctest::Approx(2.0f));
    CHECK(result.imag() == doctest::Approx(0.0f));
}

TEST_CASE("iterate: point inside Julia set reaches max_iterations") {
    IterationParams params;

    JuliaSet<double> f;
    // z=0+0i, c=-0.4+0.6i is inside the set
    auto result = iterate(Complex<double>(0.0, 0.0), Complex<double>(0.0, 0.0), f, params);
    CHECK(result.iterations == params.max_iterations);
}

TEST_CASE("iterate: point outside Julia set escapes") {
    IterationParams params;

    JuliaSet<double> f;
    // z=2+2i, c=-0.4+0.6i is clearly outside
    auto result = iterate(Complex<double>(2.0, 0.0), Complex<double>(0.0, 0.0), f, params);
    CHECK(result.iterations < params.max_iterations);
}