
#ifndef MATRIX_CALCULATOR_CONSTANTS_H
#define MATRIX_CALCULATOR_CONSTANTS_H

#pragma once

namespace core {
    inline constexpr double EPS = 1e-9;
    inline constexpr int PRINT_PRECISION = 4;

    constexpr bool isNearlyZero(const double value) {
        return value > -EPS && value < EPS;
    }
}
#endif //MATRIX_CALCULATOR_CONSTANTS_H