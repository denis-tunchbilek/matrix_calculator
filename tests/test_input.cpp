#include <sstream>

#include <gtest/gtest.h>

#include "core/errors.h"
#include "io/matrix_input.h"

using core::Matrix;
using core::ParseError;
using io::MatrixInput;

TEST(InputTest, ReadsMultilineMatrix) {
    std::istringstream input(R"(
[
1 2
3 4
]
)");

    MatrixInput reader;
    Matrix m = reader.read(input);

    EXPECT_EQ(m.rows(), 2);
    EXPECT_EQ(m.cols(), 2);

    EXPECT_DOUBLE_EQ(m.at(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(m.at(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(m.at(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(m.at(1, 1), 4.0);
}

TEST(InputTest, ReadsSingleLineMatrix) {
    std::istringstream input("[[1,2],[3,4]]");

    MatrixInput reader;
    Matrix m = reader.read(input);

    EXPECT_EQ(m.rows(), 2);
    EXPECT_EQ(m.cols(), 2);

    EXPECT_DOUBLE_EQ(m.at(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(m.at(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(m.at(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(m.at(1, 1), 4.0);
}

TEST(InputTest, ThrowsOnDifferentRowSizes) {
    std::istringstream input(R"(
[
1 2
3 4 5
]
)");

    MatrixInput reader;

    EXPECT_THROW(reader.read(input), ParseError);
}

TEST(InputTest, ThrowsOnEmptyInput) {
    std::istringstream input("");

    MatrixInput reader;

    EXPECT_THROW(reader.read(input), ParseError);
}