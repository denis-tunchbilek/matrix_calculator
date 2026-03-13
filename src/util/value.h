#pragma once

#include <string>
#include <variant>

#include "core/matrix.h"

namespace matrix::util {

    using Value = std::variant<matrix::core::Matrix, double, int, std::string>;

} // namespace matrix::util