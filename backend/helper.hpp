#pragma once

inline double safe_stod(const std::string& str) {
    double result;
    try {
        result = std::stod(str);
    } catch (std::invalid_argument&) {
        result = 0.0;
    }
    return result;
}