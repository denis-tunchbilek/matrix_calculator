#pragma once

#include <iosfwd>
#include <memory>

#include "io/matrix_printer.h"
#include "util/value.h"

namespace matrix::util {

    void printValue(std::ostream& out,
                    const Value& value,
                    const std::shared_ptr<const matrix::io::MatrixPrinter>& printer);

} // namespace matrix::util