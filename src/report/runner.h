#pragma once

#include <memory>
#include <ostream>
#include <vector>

#include "io/matrix_printer.h"
#include "report/step.h"

namespace report {

    class StepRunner {
    public:
        explicit StepRunner(std::shared_ptr<const io::MatrixPrinter> printer);

        void addStep(std::unique_ptr<Step> step);
        void run(std::ostream& out, const core::Matrix& matrix) const;

    private:
        std::vector<std::unique_ptr<Step>> steps_;
        std::shared_ptr<const io::MatrixPrinter> printer_;
    };

} // namespace report