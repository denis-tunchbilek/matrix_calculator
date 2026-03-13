#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "core/errors.h"
#include "io/matrix_input.h"
#include "io/matrix_printer.h"
#include "report/info_step.h"
#include "report/property_step.h"
#include "report/runner.h"
#include "report/transform_step.h"

namespace {
std::string readAllStdin() {
    std::ostringstream buffer;
    buffer << std::cin.rdbuf();
    return buffer.str();
}
}

int main() {
    using matrix::report::InfoStep;
    using matrix::report::PropertyStep;
    using matrix::report::StepRunner;
    using matrix::report::TransformStep;

    try {
        const matrix::io::MatrixInput input;

        std::string rawInput = readAllStdin();
        if (rawInput.find_first_not_of(" \t\n\r") == std::string::npos) {
            rawInput = "[[1,2],[3,4]]";
            std::cout << "No input provided. Using demo matrix: " << rawInput << "\n\n";
        }

        std::istringstream source(rawInput);
        const matrix::core::Matrix matrix = input.read(source);

        auto printer = std::make_shared<const matrix::io::MatrixPrinter>();

        StepRunner runner(printer);
        runner.addStep(std::make_unique<InfoStep>());
        runner.addStep(std::make_unique<TransformStep>(TransformStep::Mode::Transpose));
        runner.addStep(std::make_unique<TransformStep>(TransformStep::Mode::Rref));
        runner.addStep(std::make_unique<PropertyStep>(PropertyStep::Mode::Rank));
        runner.addStep(std::make_unique<PropertyStep>(PropertyStep::Mode::Determinant));
        runner.addStep(std::make_unique<PropertyStep>(PropertyStep::Mode::Inverse));
        runner.run(std::cout, matrix);

        return 0;
    } catch (const matrix::core::MatrixError& error) {
        std::cerr << error.what() << '\n';
    } catch (const std::exception& error) {
        std::cerr << "Unexpected error: " << error.what() << '\n';
    }
    return 1;
}