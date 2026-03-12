#include "core/linalg.h"

#include <algorithm>
#include <cmath>

#include "core/constants.h"

namespace core {
namespace {

void swapRows(Matrix& matrix, const std::size_t first, const std::size_t second) {
    if (first == second) {
        return;
    }
    for (std::size_t col = 0; col < matrix.cols(); ++col) {
        std::swap(matrix.at(first, col), matrix.at(second, col));
    }
}

}

Matrix LinAlgService::rref(const Matrix& matrix) const {
    Matrix result = matrix;

    std::size_t pivotRow = 0;
    std::size_t pivotCol = 0;

    while (pivotRow < result.rows() && pivotCol < result.cols()) {
        std::size_t bestRow = pivotRow;
        double bestAbsValue = std::abs(result.at(bestRow, pivotCol));
        for (std::size_t row = pivotRow + 1; row < result.rows(); ++row) {
            const double currentAbsValue = std::abs(result.at(row, pivotCol));
            if (currentAbsValue > bestAbsValue) {
                bestAbsValue = currentAbsValue;
                bestRow = row;
            }
        }

        if (bestAbsValue < EPS) {
            ++pivotCol;
            continue;
        }

        swapRows(result, pivotRow, bestRow);

        const double pivotValue = result.at(pivotRow, pivotCol);
        for (std::size_t col = pivotCol; col < result.cols(); ++col) {
            result.at(pivotRow, col) /= pivotValue;
        }

        for (std::size_t row = 0; row < result.rows(); ++row) {
            if (row == pivotRow) {
                continue;
            }

            const double factor = result.at(row, pivotCol);
            if (std::abs(factor) < EPS) {
                result.at(row, pivotCol) = 0.0;
                continue;
            }

            for (std::size_t col = pivotCol; col < result.cols(); ++col) {
                result.at(row, col) -= factor * result.at(pivotRow, col);
                if (isNearlyZero(result.at(row, col))) {
                    result.at(row, col) = 0.0;
                }
            }
        }

        for (std::size_t col = 0; col < result.cols(); ++col) {
            if (isNearlyZero(result.at(pivotRow, col))) {
                result.at(pivotRow, col) = 0.0;
            }
        }
        ++pivotRow;
        ++pivotCol;
    }
    return result;
}

int LinAlgService::rank(const Matrix& matrix) const {
    (void)matrix;
    return 0;
}

double LinAlgService::det(const Matrix& matrix) const {
    (void)matrix;
    return 0.0;
}

std::optional<Matrix> LinAlgService::inverse(const Matrix& matrix) const {
    (void)matrix;
    return std::nullopt;
}

}