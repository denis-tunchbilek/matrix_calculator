#include "report/runner.h"

#include <chrono>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <utility>

#include "util/value_printer.h"

namespace report {
    namespace {

        class ScopedStepTimer {
        public:
            explicit ScopedStepTimer(const std::string& stepName)
                : stepName_(stepName),
                  startedAt_(std::chrono::steady_clock::now()) {}

            ~ScopedStepTimer() {
                const auto finishedAt = std::chrono::steady_clock::now();
                const auto elapsed =
                    std::chrono::duration_cast<std::chrono::microseconds>(finishedAt - startedAt_);

                std::clog << "[timer] " << stepName_ << ": " << elapsed.count() << " us\n";
            }

        private:
            std::string stepName_;
            std::chrono::steady_clock::time_point startedAt_;
        };

    } // namespace

    StepRunner::StepRunner(std::shared_ptr<const io::MatrixPrinter> printer)
        : printer_(std::move(printer)) {}

    void StepRunner::addStep(std::unique_ptr<Step> step) {
        steps_.push_back(std::move(step));
    }

    void StepRunner::run(const core::Matrix& matrix, std::ostream& output) const {
        for (const auto& step : steps_) {
            ScopedStepTimer timer(step->name());

            output << "== " << step->name() << " ==\n";
            const auto value = step->run(matrix);
            util::printValue(output, value, printer_);
            output << "\n\n";
        }
    }

}