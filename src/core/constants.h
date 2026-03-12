
#ifndef MATRIX_CALCULATOR_CONSTANTS_H
#define MATRIX_CALCULATOR_CONSTANTS_H

#pragma once

#include <cstddef>

namespace core {
    constexpr double EPS = 1e-9;
    constexpr int PRINT_PRECISION = 4;

    constexpr bool isNearlyZero(const double value) noexcept {
        return value > -EPS && value < EPS;
    }
}
#endif //MATRIX_CALCULATOR_CONSTANTS_H