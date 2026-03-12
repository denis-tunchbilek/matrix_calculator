
#ifndef MATRIX_CALCULATOR_ERRORS_H
#define MATRIX_CALCULATOR_ERRORS_H

#pragma once

#include <stdexcept>
#include <string>

namespace core {

    class MatrixError : public std::runtime_error {
    public:
        explicit MatrixError(const std::string& message) : std::runtime_error(message) {}
    };

    class ParseError : public MatrixError {
    public:
        explicit ParseError(const std::string& message) : MatrixError(message) {}
    };

    class DimensionError : public MatrixError {
    public:
        explicit DimensionError(const std::string& message) : MatrixError(message) {}
    };

    class SingularError : public MatrixError {
    public:
        explicit SingularError(const std::string& message) : MatrixError(message) {}
    };

    class EvalError : public MatrixError {
    public:
        explicit EvalError(const std::string& message) : MatrixError(message) {}
    };

}

#endif //MATRIX_CALCULATOR_ERRORS_H