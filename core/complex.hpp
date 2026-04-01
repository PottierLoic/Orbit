#pragma once

#include <cmath>

template <typename T>
struct Complex {
public:
    constexpr Complex(): _real(0), _imag(0) {}
    constexpr Complex(const T real, const T imag) : _real(real), _imag(imag) {}

    [[nodiscard]] T real() const noexcept { return _real; }
    [[nodiscard]] T imag() const noexcept { return _imag; }

    [[nodiscard]] constexpr Complex operator+(const Complex& other) const noexcept {
      return Complex(_real + other._real, _imag + other._imag);
    }

    [[nodiscard]] constexpr Complex operator-(const Complex& other) const noexcept{
      return Complex(_real - other._real, _imag - other._imag);
    }

    [[nodiscard]] constexpr Complex operator*(const Complex& other) const noexcept{
      return Complex(_real * other._real - _imag * other._imag,
                     _real * other._imag + _imag * other._real);
    }

    [[nodiscard]] constexpr Complex operator/(const Complex& other) const {
      const T denominator = other._real * other._real + other._imag * other._imag;
      return Complex((_real * other._real + _imag * other._imag) / denominator,
                     (_imag * other._real - _real * other._imag) / denominator);
    }

    [[nodiscard]] constexpr T norm() const {
      return std::sqrt(_real * _real + _imag * _imag);
    }

    [[nodiscard]] constexpr T squared_norm() const noexcept{
      return _real * _real + _imag * _imag;
    }

    [[nodiscard]] constexpr T angle() const {
      return std::atan2(_imag, _real);
    }

private:
    T _real;
    T _imag;
};