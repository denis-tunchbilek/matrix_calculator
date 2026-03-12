#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>

#include "core/errors.h"
#include "core/matrix.h"
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

core::Matrix makeDemoMatrix() {
    return core::Matrix({
        {1.0, 2.0, 3.0},
        {0.0, 1.0, 4.0},
        {5.0, 6.0, 0.0}
    });
}

core::Matrix readInputOrFallback() {
    const std::string input = readAllStdin();
    if (input.find_first_not_of(" \t\r\n") == std::string::npos) {
        return makeDemoMatrix();
    }

    io::MatrixInput reader;
    std::istringstream stream(input);
    return reader.read(stream);
}

}

int main() {
    try {
        const core::Matrix matrix = readInputOrFallback();

        const auto printer = std::make_shared<const io::MatrixPrinter>();

        report::StepRunner runner(printer);

        runner.addStep(std::make_unique<report::InfoStep>());
        runner.addStep(std::make_unique<report::TransformStep>(
            report::TransformStep::Mode::Transpose));
        runner.addStep(std::make_unique<report::TransformStep>(
            report::TransformStep::Mode::Rref));
        runner.addStep(std::make_unique<report::PropertyStep>(
            report::PropertyStep::Mode::Rank));
        runner.addStep(std::make_unique<report::PropertyStep>(
            report::PropertyStep::Mode::Determinant));
        runner.addStep(std::make_unique<report::PropertyStep>(
            report::PropertyStep::Mode::Inverse));

        runner.run(matrix, std::cout);
        return 0;
    } catch (const core::MatrixError& error) {
        std::cerr << "Matrix error: " << error.what() << '\n';
        return 1;
    } catch (const std::exception& error) {
        std::cerr << "Unexpected error: " << error.what() << '\n';
        return 1;
    }
}