#include "util/value_printer.h"

#include <iomanip>
#include <ostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <variant>

#include "core/constants.h"
#include "io/matrix_printer.h"

namespace util {

    void printValue(std::ostream& output,
                    const Value& value,
                    const std::shared_ptr<const io::MatrixPrinter>& matrixPrinter) {
        std::visit(
            [&](const auto& storedValue) {
                using T = std::decay_t<decltype(storedValue)>;

                if constexpr (std::is_same_v<T, core::Matrix>) {
                    if (!matrixPrinter) {
                        throw std::invalid_argument(
                            "printValue requires a non-null MatrixPrinter for Matrix values"
                        );
                    }

                    matrixPrinter->print(output, storedValue);
                } else if constexpr (std::is_same_v<T, double>) {
                    const double normalized = core::isNearlyZero(storedValue) ? 0.0 : storedValue;
                    output << std::fixed << std::setprecision(core::PRINT_PRECISION) << normalized;
                } else if constexpr (std::is_same_v<T, int>) {
                    output << storedValue;
                } else if constexpr (std::is_same_v<T, std::string>) {
                    output << storedValue;
                }
            },
            value
        );
    }

} // namespace util