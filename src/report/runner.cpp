#include "report/runner.h"

#include <utility>

#include "util/value_printer.h"

namespace report {

    StepRunner::StepRunner(std::shared_ptr<const io::MatrixPrinter> printer)
        : printer_(std::move(printer)) {}

    void StepRunner::addStep(std::unique_ptr<Step> step) {
        steps_.push_back(std::move(step));
    }

    void StepRunner::run(std::ostream& out, const core::Matrix& matrix) const {
        out << "Input matrix:\n";
        printer_->print(out, matrix);
        out << "\n\nReport:\n";

        for (const auto& step : steps_) {
            out << "- " << step->name() << ":\n";
            util::printValue(out, step->run(matrix), printer_);
            out << "\n\n";
        }
    }

} // namespace report