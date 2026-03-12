#ifndef MATRIXCALCULATOR_MATRIX_H
#define MATRIXCALCULATOR_MATRIX_H
#pragma once

#include <istream>

#include "core/matrix.h"

namespace io {

    class MatrixInput {
    public:
        [[nodiscard]] core::Matrix read(std::istream& input) const;
    };

} // namespace io
#endif //MATRIXCALCULATOR_MATRIX_H