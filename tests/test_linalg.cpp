#include <gtest/gtest.h>
#include "core/linalg.h"

namespace {

    matrix::core::Matrix make22() {
        matrix::core::Matrix matrix(2, 2);
        matrix.at(0, 0) = 1.0;
        matrix.at(0, 1) = 2.0;
        matrix.at(1, 0) = 3.0;
        matrix.at(1, 1) = 4.0;
        return matrix;
    }

}

TEST(LinAlgTest, ComputesRref) {
    const matrix::core::LinAlgService service;
    const auto matrix = make22();

    const auto reduced = service.rref(matrix);

    EXPECT_NEAR(reduced.at(0, 0), 1.0, 1e-9);
    EXPECT_NEAR(reduced.at(0, 1), 0.0, 1e-9);
    EXPECT_NEAR(reduced.at(1, 0), 0.0, 1e-9);
    EXPECT_NEAR(reduced.at(1, 1), 1.0, 1e-9);
}

TEST(LinAlgTest, ComputesRankAndDeterminant) {
    const matrix::core::LinAlgService service;
    const auto matrix = make22();

    EXPECT_EQ(service.rank(matrix), 2);
    EXPECT_NEAR(service.det(matrix), -2.0, 1e-9);
}

TEST(LinAlgTest, ComputesInverseAsOptional) {
    const matrix::core::LinAlgService service;
    const auto matrix = make22();

    const auto inverse = service.inverse(matrix);

    ASSERT_TRUE(inverse.has_value());
    EXPECT_NEAR(inverse->at(0, 0), -2.0, 1e-9);
    EXPECT_NEAR(inverse->at(0, 1), 1.0, 1e-9);
    EXPECT_NEAR(inverse->at(1, 0), 1.5, 1e-9);
    EXPECT_NEAR(inverse->at(1, 1), -0.5, 1e-9);
}

TEST(LinAlgTest, ReturnsNulloptForSingularMatrix) {
    matrix::core::Matrix matrix(2, 2);
    matrix.at(0, 0) = 1.0;
    matrix.at(0, 1) = 2.0;
    matrix.at(1, 0) = 2.0;
    matrix.at(1, 1) = 4.0;

    const matrix::core::LinAlgService service;
    const auto inverse = service.inverse(matrix);

    EXPECT_FALSE(inverse.has_value());
}