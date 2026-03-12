#include "io/matrix_printer.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "core/constants.h"

namespace io {
    namespace {

        [[nodiscard]] std::string formatCell(const double value) {
            const double normalized = core::isNearlyZero(value) ? 0.0 : value;

            std::ostringstream stream;
            stream << std::fixed << std::setprecision(core::PRINT_PRECISION) << normalized;
            return stream.str();
        }

    } // namespace

    void MatrixPrinter::print(std::ostream& output, const core::Matrix& matrix) const {
        if (matrix.rows() == 0 || matrix.cols() == 0) {
            output << "[]";
            return;
        }

        std::vector<std::vector<std::string>> formatted(
            matrix.rows(),
            std::vector<std::string>(matrix.cols())
        );

        std::size_t cellWidth = 0;
        for (std::size_t row = 0; row < matrix.rows(); ++row) {
            for (std::size_t col = 0; col < matrix.cols(); ++col) {
                formatted[row][col] = formatCell(matrix.at(row, col));
                cellWidth = std::max(cellWidth, formatted[row][col].size());
            }
        }

        output << "[\n";
        for (std::size_t row = 0; row < matrix.rows(); ++row) {
            output << "  ";
            for (std::size_t col = 0; col < matrix.cols(); ++col) {
                output << std::setw(static_cast<int>(cellWidth)) << formatted[row][col];
                if (col + 1 < matrix.cols()) {
                    output << ' ';
                }
            }
            output << '\n';
        }
        output << ']';
    }

} // namespace io