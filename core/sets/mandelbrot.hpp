#pragma once

#include "../complex.hpp"

template <typename T>
struct MandelbrotSet {
    [[nodiscard]] Complex<T> operator()(const Complex<T>& z, const Complex<T>& c) const { return z * z + c;}
    [[nodiscard]] bool cardioid_check(const Complex<T>& c) const {
        T x = c.real() - 0.25;
        T y = c.imag();
        T q = x * x + y * y;
        if (q * (q + x) <= 0.25 * y * y) {
            return true;
        }

        T dx = c.real() + 1.0;
        if (dx * dx + c.imag() * c.imag() <= 0.0625) {
            return true;
        }

        return false;
    }
};