#include <doctest/doctest.h>
#include "sets/mandelbrot.hpp"
#include "iterate.hpp"

TEST_CASE("MandelbrotSet: iteration formula z^2+c") {
    MandelbrotSet<double> f;
    // z=1+1i, c=0+0i => z^2 = 0+2i
    auto result = f(Complex<double>(1.0, 1.0), Complex<double>(0.0, 0.0));
    CHECK(result.real() == doctest::Approx(0.0));
    CHECK(result.imag() == doctest::Approx(2.0));
}

TEST_CASE("MandelbrotSet: c is added to z^2") {
    MandelbrotSet<double> f;
    // z=1+0i, c=2+3i => z^2+c = 1+0i + 2+3i = 3+3i
    auto result = f(Complex<double>(1.0, 0.0), Complex<double>(2.0, 3.0));
    CHECK(result.real() == doctest::Approx(3.0));
    CHECK(result.imag() == doctest::Approx(3.0));
}

TEST_CASE("MandelbrotSet: works with float") {
    MandelbrotSet<float> f;
    auto result = f(Complex<float>(1.0f, 0.0f), Complex<float>(1.0f, 0.0f));
    CHECK(result.real() == doctest::Approx(2.0f));
    CHECK(result.imag() == doctest::Approx(0.0f));
}

TEST_CASE("MandelbrotSet cardioid_check: origin is inside main cardioid") {
    MandelbrotSet<double> f;
    CHECK(f.cardioid_check(Complex<double>(0.0, 0.0)) == true);
}

TEST_CASE("MandelbrotSet cardioid_check: (-1,0) is on the period-2 bulb boundary") {
    MandelbrotSet<double> f;
    // The period-2 bulb check: (c.real+1)^2 + c.imag^2 <= 0.0625
    // At c=(-1,0): 0^2 + 0 = 0 <= 0.0625 => inside
    CHECK(f.cardioid_check(Complex<double>(-1.0, 0.0)) == true);
}

TEST_CASE("MandelbrotSet cardioid_check: far outside returns false") {
    MandelbrotSet<double> f;
    CHECK(f.cardioid_check(Complex<double>(2.0, 2.0)) == false);
    CHECK(f.cardioid_check(Complex<double>(-2.0, 0.0)) == false);
    CHECK(f.cardioid_check(Complex<double>(0.0, 2.0)) == false);
}

TEST_CASE("MandelbrotSet cardioid_check: point inside main cardioid body") {
    MandelbrotSet<double> f;
    // c = 0.25+0i is just inside the main cardioid
    CHECK(f.cardioid_check(Complex<double>(0.25, 0.0)) == true);
}

TEST_CASE("MandelbrotSet cardioid_check: point near cardioid tip escapes") {
    MandelbrotSet<double> f;
    // c = 0.5+0i is just outside the main cardioid (tip is at 0.25)
    CHECK(f.cardioid_check(Complex<double>(0.5, 0.0)) == false);
}

TEST_CASE("MandelbrotSet cardioid_check: symmetric about real axis") {
    MandelbrotSet<double> f;
    Complex<double> c_pos(0.0, 0.1);
    Complex<double> c_neg(0.0, -0.1);
    CHECK(f.cardioid_check(c_pos) == f.cardioid_check(c_neg));
}

TEST_CASE("iterate: point inside Mandelbrot set reaches max_iterations") {
    IterationParams params;
    params.max_iterations = 200;

    MandelbrotSet<double> f;
    // c = 0+0i is inside the set
    auto result = iterate(Complex<double>(0.0, 0.0), Complex<double>(0.0, 0.0), f, params);
    CHECK(result.iterations == params.max_iterations);
}

TEST_CASE("iterate: point outside Mandelbrot set escapes") {
    IterationParams params;
    params.max_iterations = 200;

    MandelbrotSet<double> f;
    // c = 2+2i is clearly outside
    auto result = iterate(Complex<double>(0.0, 0.0), Complex<double>(2.0, 2.0), f, params);
    CHECK(result.iterations < params.max_iterations);
}
