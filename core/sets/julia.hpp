#pragma once

#include "complex.hpp"

template <typename T>
struct JuliaSet {
    [[nodiscard]] Complex<T> operator()(const Complex<T>& z, const Complex<T>& c) const { return z * z + c;}
    [[nodiscard]] std::pair<Complex<T>, Complex<T>> make_zc(const Complex<T>& pixel, const Complex<T>& c) const {
        return {pixel, c};
    }
};