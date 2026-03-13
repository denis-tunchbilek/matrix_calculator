#include "report/runner.h"

#include <chrono>
#include <iostream>
#include <memory>
#include <ostream>
#include <utility>

#include "util/value_printer.h"

namespace matrix::report {
    namespace {

        class ScopedStepTimer {
        public:
            explicit ScopedStepTimer(const std::string& stepName)
                : stepName_(stepName), started_(std::chrono::steady_clock::now()) {}

            ~ScopedStepTimer() {
                const auto finished = std::chrono::steady_clock::now();
                const auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(finished - started_);
                std::clog << "[timer] " << stepName_ << ": " << elapsed.count() << " us\n";
            }

        private:
            std::string stepName_;
            std::chrono::steady_clock::time_point started_;
        };

    } // namespace

    StepRunner::StepRunner(std::shared_ptr<const matrix::io::MatrixPrinter> printer) : printer_(std::move(printer)) {}

    void StepRunner::addStep(std::unique_ptr<Step> step) {
        steps_.push_back(std::move(step));
    }

    void StepRunner::run(std::ostream& out, const matrix::core::Matrix& matrix) const {
        out << "=== Input matrix ===\n";
        printer_->print(out, matrix);
        out << "\n\n=== Report ===\n";

        for (const auto& step : steps_) {
            ScopedStepTimer timer(step->name());
            out << "-- " << step->name() << " --\n";
            const auto value = step->run(matrix);
            matrix::util::printValue(out, value, printer_);
            out << "\n\n";
        }
    }

}