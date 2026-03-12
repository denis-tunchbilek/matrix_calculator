#pragma once

#include <string>

#include "core/matrix.h"
#include "util/value.h"

namespace matrix::report {

    class Step {
    public:
        virtual ~Step() = default;

        virtual std::string name() const = 0;
        virtual matrix::util::Value run(const matrix::core::Matrix& matrix) = 0;
    };

}