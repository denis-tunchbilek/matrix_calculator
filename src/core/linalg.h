#ifndef MATRIX_CALCULATOR_LINALG_H
#define MATRIX_CALCULATOR_LINALG_H

#pragma once

#include <optional>
#include "core/matrix.h"

namespace core {

    class LinAlgService {
    public:
        [[nodiscard]] Matrix rref(const Matrix& matrix) const;
        [[nodiscard]] int rank(const Matrix& matrix) const;
        [[nodiscard]] double det(const Matrix& matrix) const;
        [[nodiscard]] std::optional<Matrix> inverse(const Matrix& matrix) const;
    };

} // namespace core

#endif // MATRIX_CALCULATOR_LINALG_H