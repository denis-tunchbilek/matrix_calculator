#include "util/value_printer.h"

#include <type_traits>
#include <variant>

namespace util {

    void printValue(std::ostream& out,
                    const Value& value,
                    const std::shared_ptr<const io::MatrixPrinter>& printer) {
        std::visit(
            [&](const auto& item) {
                using T = std::decay_t<decltype(item)>;

                if constexpr (std::is_same_v<T, core::Matrix>) {
                    printer->print(out, item);
                } else {
                    out << item;
                }
            },
            value
        );
    }

} // namespace util