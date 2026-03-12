#ifndef MATRIXCALCULATOR_MATRIX_PRINTER_H
#define MATRIXCALCULATOR_MATRIX_PRINTER_H
#pragma once

#include <iosfwd>

#include "core/matrix.h"

namespace io {

    class MatrixPrinter {
    public:
        void print(std::ostream& output, const core::Matrix& matrix) const;
    };

} // namespace io
#endif //MATRIXCALCULATOR_MATRIX_PRINTER_H