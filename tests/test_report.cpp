#include <gtest/gtest.h>

#include <memory>
#include <sstream>

#include "report/info_step.h"
#include "report/property_step.h"
#include "report/runner.h"
#include "report/transform_step.h"

TEST(ReportTest, RunsFullReportWithoutCrashing) {
    core::Matrix matrix(2, 2);
    matrix.at(0, 0) = 1.0;
    matrix.at(0, 1) = 2.0;
    matrix.at(1, 0) = 3.0;
    matrix.at(1, 1) = 4.0;

    auto printer = std::make_shared<const io::MatrixPrinter>();
    report::StepRunner runner(printer);
    runner.addStep(std::make_unique<report::InfoStep>());
    runner.addStep(std::make_unique<report::TransformStep>(
        report::TransformStep::Mode::Transpose));
    runner.addStep(std::make_unique<report::PropertyStep>(
        report::PropertyStep::Mode::Rank));

    std::ostringstream out;
    runner.run(out, matrix);

    EXPECT_NE(out.str().find("Matrix info"), std::string::npos);
    EXPECT_NE(out.str().find("Transpose"), std::string::npos);
    EXPECT_NE(out.str().find("Rank"), std::string::npos);
}