#pragma once

#include <memory>
#include <ostream>
#include <vector>

#include "core/matrix.h"
#include "report/step.h"

namespace report {

    class StepRunner {
    public:
        void addStep(std::unique_ptr<Step> step);

        void run(const core::Matrix& matrix, std::ostream& output) const;

    private:
        std::vector<std::unique_ptr<Step>> steps_;
    };

}