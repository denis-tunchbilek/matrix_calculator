//
// Created by Денис on 12.03.2026.
//

#ifndef MATRIXCALCULATOR_VALUE_H
#define MATRIXCALCULATOR_VALUE_H
#pragma once

#include <string>
#include <variant>

#include "core/matrix.h"

namespace util {

    using Value = std::variant<core::Matrix, double, int, std::string>;

} // namespace util
#endif //MATRIXCALCULATOR_VALUE_H