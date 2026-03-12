#include "core/linalg.h"

#include <algorithm>
#include <cmath>
#include <optional>

#include "core/constants.h"
#include "core/errors.h"

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
    const Matrix reduced = rref(matrix);
    int result = 0;

    for (std::size_t row = 0; row < reduced.rows(); ++row) {
        bool nonZeroRow = false;

        for (std::size_t col = 0; col < reduced.cols(); ++col) {
            if (!isNearlyZero(reduced.at(row, col))) {
                nonZeroRow = true;
                break;
            }
        }
        if (nonZeroRow) {
            ++result;
        }
    }
    return result;
}

double LinAlgService::det(const Matrix& matrix) const {
    if (matrix.rows() != matrix.cols()) {
        throw DimensionError("Determinant is defined only for square matrices");
    }
    Matrix working = matrix;
    double determinant = 1.0;
    int swapCount = 0;

    for (std::size_t pivotCol = 0; pivotCol < working.cols(); ++pivotCol) {
        std::size_t bestRow = pivotCol;
        double bestAbsValue = std::abs(working.at(bestRow, pivotCol));


    for (std::size_t row = pivotCol + 1; row < working.rows(); ++row) {
            const double currentAbsValue = std::abs(working.at(row, pivotCol));
            if (currentAbsValue > bestAbsValue) {
                bestAbsValue = currentAbsValue;
                bestRow = row;
            }
        }

        if (bestAbsValue < EPS) {
            return 0.0;
        }

        if (bestRow != pivotCol) {
            swapRows(working, bestRow, pivotCol);
            ++swapCount;
        }

        const double pivotValue = working.at(pivotCol, pivotCol);
        determinant *= pivotValue;

        for (std::size_t row = pivotCol + 1; row < working.rows(); ++row) {
            const double factor = working.at(row, pivotCol) / pivotValue;

            for (std::size_t col = pivotCol; col < working.cols(); ++col) {
                working.at(row, col) -= factor * working.at(pivotCol, col);
                if (isNearlyZero(working.at(row, col))) {
                    working.at(row, col) = 0.0;
                }
            }
        }
    }

    if (swapCount % 2 != 0) {
        determinant = -determinant;
    }
    return isNearlyZero(determinant) ? 0.0 : determinant;
}

std::optional<Matrix> LinAlgService::inverse(const Matrix& matrix) const {
    if (matrix.rows() != matrix.cols()) {
        throw DimensionError("Inverse is defined only for square matrices");
    }

    const std::size_t n = matrix.rows();
    Matrix left = matrix;
    Matrix right = Matrix::identity(n);

    for (std::size_t pivotCol = 0; pivotCol < n; ++pivotCol) {
        std::size_t bestRow = pivotCol;
        double bestAbsValue = std::abs(left.at(bestRow, pivotCol));

        for (std::size_t row = pivotCol + 1; row < n; ++row) {
            const double currentAbsValue = std::abs(left.at(row, pivotCol));
            if (currentAbsValue > bestAbsValue) {
                bestAbsValue = currentAbsValue;
                bestRow = row;
            }
        }

        if (bestAbsValue < EPS) {
            return std::nullopt;
        }

        if (bestRow != pivotCol) {
            swapRows(left, bestRow, pivotCol);
            swapRows(right, bestRow, pivotCol);
        }

        const double pivotValue = left.at(pivotCol, pivotCol);

        for (std::size_t col = 0; col < n; ++col) {
            left.at(pivotCol, col) /= pivotValue;
            right.at(pivotCol, col) /= pivotValue;
        }

        for (std::size_t row = 0; row < n; ++row) {
            if (row == pivotCol) {
                continue;
            }

            const double factor = left.at(row, pivotCol);
            if (std::abs(factor) < EPS) {
                left.at(row, pivotCol) = 0.0;
                continue;
            }

            for (std::size_t col = 0; col < n; ++col) {
                left.at(row, col) -= factor * left.at(pivotCol, col);
                right.at(row, col) -= factor * right.at(pivotCol, col);

                if (isNearlyZero(left.at(row, col))) {
                    left.at(row, col) = 0.0;
                }
                if (isNearlyZero(right.at(row, col))) {
                    right.at(row, col) = 0.0;
                }
            }
        }
    }

    return right;
}

}