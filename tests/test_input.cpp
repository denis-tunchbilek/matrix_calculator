#include <cassert>
#include <sstream>
#include <string>

#include "core/errors.h"
#include "io/matrix_input.h"

using core::Matrix;
using core::ParseError;
using io::MatrixInput;

void test_multiline_matrix() {
    std::istringstream input(R"(
[
1 2
3 4
]
)");

    MatrixInput reader;
    Matrix m = reader.read(input);

    assert(m.rows() == 2);
    assert(m.cols() == 2);

    assert(m.at(0,0) == 1);
    assert(m.at(0,1) == 2);
    assert(m.at(1,0) == 3);
    assert(m.at(1,1) == 4);
}

void test_singleline_matrix() {
    std::istringstream input("[[1,2],[3,4]]");

    MatrixInput reader;
    Matrix m = reader.read(input);

    assert(m.rows() == 2);
    assert(m.cols() == 2);

    assert(m.at(0,0) == 1);
    assert(m.at(0,1) == 2);
    assert(m.at(1,0) == 3);
    assert(m.at(1,1) == 4);
}

void test_bad_row_sizes() {
    std::istringstream input(R"(
[
1 2
3 4 5
]
)");

    MatrixInput reader;

    bool thrown = false;

    try {
        reader.read(input);
    } catch (const ParseError&) {
        thrown = true;
    }

    assert(thrown);
}

int main() {
    test_multiline_matrix();
    test_singleline_matrix();
    test_bad_row_sizes();

    return 0;
}