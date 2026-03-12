#include "report/info_step.h"

#include <string>

namespace matrix::report {

    std::string InfoStep::name() const {
        return "Matrix info";
    }

    matrix::util::Value InfoStep::run(const matrix::core::Matrix& matrix) {
        const bool isSquare = matrix.rows() == matrix.cols();
        const std::size_t elements = matrix.rows() * matrix.cols();

        std::string result;
        result += "rows: " + std::to_string(matrix.rows()) + "\n";
        result += "cols: " + std::to_string(matrix.cols()) + "\n";
        result += "square: " + std::string(isSquare ? "yes" : "no") + "\n";
        result += "elements: " + std::to_string(elements);

        return result;
    }

}