#ifndef MATRIX_CALCULATOR_MATRIX_H
#define MATRIX_CALCULATOR_MATRIX_H

#pragma once
#include <cstddef>
#include <vector>

namespace core {

    class Matrix {
    public:
        Matrix() = default;
        Matrix(std::size_t rows, std::size_t cols);
        Matrix(std::size_t rows, std::size_t cols, std::vector<double> values);

        [[nodiscard]] std::size_t rows() const noexcept;
        [[nodiscard]] std::size_t cols() const noexcept;

        [[nodiscard]] double& at(std::size_t row, std::size_t col);
        [[nodiscard]] const double& at(std::size_t row, std::size_t col) const;

        [[nodiscard]] const std::vector<double>& raw() const noexcept;
        [[nodiscard]] std::vector<double>& raw() noexcept;

        [[nodiscard]] static Matrix identity(std::size_t size);
        [[nodiscard]] Matrix transpose() const;

        [[nodiscard]] Matrix operator+(const Matrix& other) const;
        [[nodiscard]] Matrix operator-(const Matrix& other) const;
        [[nodiscard]] Matrix operator*(const Matrix& other) const;
        [[nodiscard]] Matrix operator*(double scalar) const;

    private:
        [[nodiscard]] std::size_t index(std::size_t row, std::size_t col) const noexcept;

        std::size_t rows_{0};
        std::size_t cols_{0};
        std::vector<double> data_{};
    };

} // namespace matrix::core

#endif // MATRIX_CALCULATOR_MATRIX_H