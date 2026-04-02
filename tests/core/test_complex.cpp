#include <doctest/doctest.h>
#include "complex.hpp"
#include <numbers>

TEST_CASE("default construction initializes to zero") {
    Complex<double> z;
    CHECK(z.real() == 0.0);
    CHECK(z.imag() == 0.0);
}

TEST_CASE("construction from real and imaginary parts") {
    Complex<double> z(3.0, -4.0);
    CHECK(z.real() == 3.0);
    CHECK(z.imag() == -4.0);
}

TEST_CASE("template works with float") {
    Complex<float> z(1.0f, 2.0f);
    CHECK(z.real() == 1.0f);
    CHECK(z.imag() == 2.0f);
}

TEST_CASE("addition") {
    Complex<double> result = Complex<double>(1.0, 2.0) + Complex<double>(3.0, -1.0);
    CHECK(result.real() == 4.0);
    CHECK(result.imag() == 1.0);
}

TEST_CASE("subtraction") {
    Complex<double> result = Complex<double>(5.0, 3.0) - Complex<double>(2.0, 7.0);
    CHECK(result.real() == 3.0);
    CHECK(result.imag() == -4.0);
}

TEST_CASE("multiplication: (1+2i)(3+4i) = -5+10i") {
    Complex<double> result = Complex<double>(1.0, 2.0) * Complex<double>(3.0, 4.0);
    CHECK(result.real() == doctest::Approx(-5.0));
    CHECK(result.imag() == doctest::Approx(10.0));
}

TEST_CASE("squaring: (2+1i)^2 = 3+4i") {
    Complex<double> z(2.0, 1.0);
    Complex<double> result = z * z;
    CHECK(result.real() == doctest::Approx(3.0));
    CHECK(result.imag() == doctest::Approx(4.0));
}

TEST_CASE("division: (2+4i)/(1+2i) = 2+0i") {
    // denom = 1+4=5, real=(2+8)/5=2, imag=(4-4)/5=0
    Complex<double> result = Complex<double>(2.0, 4.0) / Complex<double>(1.0, 2.0);
    CHECK(result.real() == doctest::Approx(2.0));
    CHECK(result.imag() == doctest::Approx(0.0));
}

TEST_CASE("norm (modulus): |3+4i| = 5") {
    CHECK(Complex<double>(3.0, 4.0).norm() == doctest::Approx(5.0));
}

TEST_CASE("squared_norm: |3+4i|^2 = 25") {
    CHECK(Complex<double>(3.0, 4.0).squared_norm() == 25.0);
}

TEST_CASE("squared_norm with negative components") {
    CHECK(Complex<double>(-3.0, -4.0).squared_norm() == 25.0);
}

TEST_CASE("angle") {
    CHECK(Complex<double>(1.0, 0.0).angle() == doctest::Approx(0.0));
    CHECK(Complex<double>(0.0, 1.0).angle() == doctest::Approx(std::numbers::pi / 2.0));
    CHECK(Complex<double>(1.0, 1.0).angle() == doctest::Approx(std::numbers::pi / 4.0));
}