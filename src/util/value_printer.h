#ifndef MATRIXCALCULATOR_VALUE_PRINTER_H
#define MATRIXCALCULATOR_VALUE_PRINTER_H
#pragma once

#include <memory>
#include <ostream>

#include "util/value.h"

namespace io {
    class MatrixPrinter;
}

namespace util {

    void printValue(std::ostream& output,
                    const Value& value,
                    const std::shared_ptr<const io::MatrixPrinter>& matrixPrinter);

} // namespace util
#endif //MATRIXCALCULATOR_VALUE_PRINTER_H