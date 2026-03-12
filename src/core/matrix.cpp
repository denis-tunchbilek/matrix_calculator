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

    Matrix Matrix::identity(std::size_t size) {
        Matrix result(size, size);
        for (std::size_t i = 0; i < size; ++i) {
            result.at(i, i) = 1.0;
        }
        return result;
    }

    Matrix Matrix::transpose() const {
        Matrix result(cols_, rows_);
        for (std::size_t row = 0; row < rows_; ++row) {
            for (std::size_t col = 0; col < cols_; ++col) {
                result.at(col, row) = at(row, col);
            }
        }
        return result;
    }

    Matrix Matrix::operator*(const Matrix& other) const {
        if (cols_ != other.rows_) {
            throw DimensionError(
                "Cannot multiply matrices of sizes " + std::to_string(rows_) + "x" +
                std::to_string(cols_) + " and " + std::to_string(other.rows_) +
                "x" + std::to_string(other.cols_)
            );
        }

        Matrix result(rows_, other.cols_);
        for (std::size_t row = 0; row < rows_; ++row) {
            for (std::size_t col = 0; col < other.cols_; ++col) {
                double sum = 0.0;
                for (std::size_t k = 0; k < cols_; ++k) {
                    sum += at(row, k) * other.at(k, col);
                }
                result.at(row, col) = sum;
            }
        }
        return result;
    }

    Matrix Matrix::operator*(double scalar) const {
        Matrix result(rows_, cols_);
        for (std::size_t i = 0; i < data_.size(); ++i) {
            result.raw()[i] = data_[i] * scalar;
        }
        return result;
    }

    Matrix Matrix::operator+(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw DimensionError(
                "Cannot add matrices of sizes " + std::to_string(rows_) + "x" +
                std::to_string(cols_) + " and " + std::to_string(other.rows_) +
                "x" + std::to_string(other.cols_)
            );
        }

        Matrix result(rows_, cols_);
        for (std::size_t i = 0; i < data_.size(); ++i) {
            result.raw()[i] = data_[i] + other.raw()[i];
        }
        return result;
    }

    Matrix Matrix::operator-(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw DimensionError(
                "Cannot subtract matrices of sizes " + std::to_string(rows_) + "x" +
                std::to_string(cols_) + " and " + std::to_string(other.rows_) +
                "x" + std::to_string(other.cols_)
            );
        }

        Matrix result(rows_, cols_);
        for (std::size_t i = 0; i < data_.size(); ++i) {
            result.raw()[i] = data_[i] - other.raw()[i];
        }
        return result;
    }

    std::size_t Matrix::index(std::size_t row, std::size_t col) const noexcept {
        return row * cols_ + col;
    }
}