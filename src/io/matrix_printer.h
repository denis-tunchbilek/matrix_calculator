#pragma once

#include <iosfwd>

#include "core/matrix.h"

namespace matrix::io {

    class MatrixPrinter {
    public:
        void print(std::ostream& out, const matrix::core::Matrix& matrix) const;
    };

} // namespace matrix::io