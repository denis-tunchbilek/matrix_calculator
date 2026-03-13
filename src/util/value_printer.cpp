#include "util/value_printer.h"

#include <ostream>
#include <utility>
#include <variant>

namespace matrix::util {

    void printValue(std::ostream& out,
                    const Value& value,
                    const std::shared_ptr<const matrix::io::MatrixPrinter>& printer) {
        std::visit(
            [&](const auto& current) {
                using T = std::decay_t<decltype(current)>;
                if constexpr (std::is_same_v<T, matrix::core::Matrix>) {
                    printer->print(out, current);
                } else {
                    out << current;
                }
            },
            value);
    }

} // namespace matrix::util