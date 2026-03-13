#include "io/matrix_printer.h"

#include <cmath>
#include <iomanip>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "core/constants.h"

namespace matrix::io {

    void MatrixPrinter::print(std::ostream& out, const matrix::core::Matrix& matrix) const {
        std::vector<std::vector<std::string>> cells(static_cast<std::size_t>(matrix.rows()),
                                                    std::vector<std::string>(static_cast<std::size_t>(matrix.cols())));
        std::vector<std::size_t> widths(static_cast<std::size_t>(matrix.cols()), 0);

        for (int r = 0; r < matrix.rows(); ++r) {
            for (int c = 0; c < matrix.cols(); ++c) {
                double value = matrix.at(r, c);
                if (std::abs(value) < matrix::core::EPS) {
                    value = 0.0;
                }
                std::ostringstream formatter;
                formatter << std::fixed << std::setprecision(matrix::core::PRINT_PRECISION) << value;
                cells[static_cast<std::size_t>(r)][static_cast<std::size_t>(c)] = formatter.str();
                widths[static_cast<std::size_t>(c)] =
                    std::max(widths[static_cast<std::size_t>(c)], formatter.str().size());
            }
        }

        out << "[\n";
        for (int r = 0; r < matrix.rows(); ++r) {
            out << "  ";
            for (int c = 0; c < matrix.cols(); ++c) {
                out << std::setw(static_cast<int>(widths[static_cast<std::size_t>(c)]))
                    << cells[static_cast<std::size_t>(r)][static_cast<std::size_t>(c)];
                if (c + 1 != matrix.cols()) {
                    out << ' ';
                }
            }
            out << '\n';
        }
        out << ']';
    }

} // namespace matrix::io