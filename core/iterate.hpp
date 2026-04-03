#pragma once

#include "complex.hpp"
#include "pixel_value.hpp"
#include "iteration_params.hpp"

template <typename T, typename Func>
[[nodiscard]] PixelValue iterate(Complex<T> z, const Complex<T>& c, Func f, const IterationParams& params) {
    if constexpr (requires { f.cardioid_check(c); }) {
        if (params.cardioid_check && f.cardioid_check(c)) {
            return PixelValue{params.max_iterations, Complex<double>(0, 0)};
        }
    }

    uint32_t i = 0;
    while (i < params.max_iterations && z.squared_norm() < 4.0) {
        z = f(z, c);
        i++;
    }
    return PixelValue{i, Complex<double>(static_cast<double>(z.real()), static_cast<double>(z.imag()))};
}
