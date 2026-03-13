#include "report/runner.h"

#include <chrono>
#include <iostream>
#include <utility>

#include "util/value_printer.h"

namespace report {
    namespace {

        class ScopedStepTimer {
        public:
            ScopedStepTimer(std::ostream& out, std::string stepName)
                : out_(out),
                  stepName_(std::move(stepName)),
                  start_(std::chrono::steady_clock::now()) {}

            ~ScopedStepTimer() {
                const auto finish = std::chrono::steady_clock::now();
                const auto elapsed =
                    std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count();

                out_ << "\n[timer] " << stepName_ << ": " << elapsed << " us\n";
            }

        private:
            std::ostream& out_;
            std::string stepName_;
            std::chrono::steady_clock::time_point start_;
        };

    }

    StepRunner::StepRunner(std::shared_ptr<const io::MatrixPrinter> printer)
        : printer_(std::move(printer)) {}

    void StepRunner::addStep(std::unique_ptr<Step> step) {
        steps_.push_back(std::move(step));
    }

    void StepRunner::run(std::ostream& out, const core::Matrix& matrix) const {
        out << "=== Input matrix ===\n";
        printer_->print(out, matrix);
        out << "\n\n=== Report ===\n";

        for (const auto& step : steps_) {
            out << "-- " << step->name() << " --\n";

            {
                ScopedStepTimer timer(out, step->name());
                util::printValue(out, step->run(matrix), printer_);
            }

            out << '\n';
        }
    }

}