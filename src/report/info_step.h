#pragma once

#include "report/step.h"

namespace matrix::report {

    class InfoStep : public Step {
    public:
        std::string name() const override;
        matrix::util::Value run(const matrix::core::Matrix& matrix) override;
    };

}