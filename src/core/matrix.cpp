#include "core/matrix.h"

#include <stdexcept>
#include <string>
#include <utility>

#include "core/errors.h"

namespace core {

    Matrix::Matrix(std::size_t rows, std::size_t cols) : rows_(rows), cols_(cols), data_(rows * cols, 0.0) {}

    Matrix::Matrix(std::size_t rows, std::size_t cols, std::vector<double> values) : rows_(rows), cols_(cols), data_(std::move(values)) {
        if (data_.size() != rows_ * cols_) {
            throw DimensionError("Matrix constructor received wrong number of elements: expected " + std::to_string(rows_ * cols_) + ", got " + std::to_string(data_.size()));
        }
    }

    std::size_t Matrix::rows() const noexcept {
        return rows_;
    }

    std::size_t Matrix::cols() const noexcept {
        return cols_;
    }

    double& Matrix::at(std::size_t row, std::size_t col) {
        if (row >= rows_ || col >= cols_) {
            throw MatrixError("Matrix index out of range: (" + std::to_string(row) + ", " + std::to_string(col) + ") for matrix of size " + std::to_string(rows_) + "x" + std::to_string(cols_));
        }
        return data_[index(row, col)];
    }

    const double& Matrix::at(std::size_t row, std::size_t col) const {
        if (row >= rows_ || col >= cols_) {
            throw MatrixError("Matrix index out of range: (" + std::to_string(row) + ", " +std::to_string(col) + ") for matrix of size " + std::to_string(rows_) + "x" + std::to_string(cols_));
        }
        return data_[index(row, col)];
    }

    const std::vector<double>& Matrix::raw() const noexcept {
        return data_;
    }

    std::vector<double>& Matrix::raw() noexcept {
        return data_;
    }

    std::size_t Matrix::index(std::size_t row, std::size_t col) const noexcept {
        return row * cols_ + col;
    }
}