#include <gtest/gtest.h>

#include <memory>
#include <sstream>

#include "io/matrix_printer.h"
#include "util/value_printer.h"

TEST(MatrixPrinterTest, NormalizesAlmostZeroToZero) {
    core::Matrix matrix(1, 2);
    matrix.at(0, 0) = 1e-12;
    matrix.at(0, 1) = 2.5;

    io::MatrixPrinter printer;
    std::ostringstream out;
    printer.print(out, matrix);

    EXPECT_NE(out.str().find("0.0000"), std::string::npos);
    EXPECT_NE(out.str().find("2.5000"), std::string::npos);
}

TEST(ValuePrinterTest, PrintsVariantUsingVisit) {
    auto printer = std::make_shared<const io::MatrixPrinter>();
    std::ostringstream out;

    util::printValue(out, util::Value(std::string("hello")), printer);

    EXPECT_EQ(out.str(), "hello");
}