#pragma once

#include <memory>
#include <ostream>

#include "io/matrix_printer.h"
#include "util/value.h"

namespace util {

    void printValue(std::ostream& out,
                    const Value& value,
                    const std::shared_ptr<const io::MatrixPrinter>& printer);

} // namespace util