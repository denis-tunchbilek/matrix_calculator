#include "io/matrix_input.h"

#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "core/errors.h"

namespace io {
namespace {

[[nodiscard]] std::string trim(const std::string& text) {
    const std::size_t begin = text.find_first_not_of(" \t\r\n");
    if (begin == std::string::npos) {
        return {};
    }

    const std::size_t end = text.find_last_not_of(" \t\r\n");
    return text.substr(begin, end - begin + 1);
}

[[nodiscard]] core::Matrix buildMatrix(const std::vector<std::vector<double>>& rows) {
    if (rows.empty()) {
        throw core::ParseError("Matrix must contain at least one row");
    }

    const std::size_t columnCount = rows.front().size();
    if (columnCount == 0) {
        throw core::ParseError("Matrix rows must contain at least one number");
    }

    std::vector<double> values;
    values.reserve(rows.size() * columnCount);

    for (std::size_t rowIndex = 0; rowIndex < rows.size(); ++rowIndex) {
        if (rows[rowIndex].size() != columnCount) {
            throw core::ParseError("Matrix rows must have the same number of elements");
        }

        values.insert(values.end(), rows[rowIndex].begin(), rows[rowIndex].end());
    }

    return core::Matrix(rows.size(), columnCount, std::move(values));
}

} // namespace

core::Matrix MatrixInput::read(std::istream& input) const {
    std::vector<std::vector<double>> rows;

    std::string line;
    bool opened = false;
    bool closed = false;

    while (std::getline(input, line)) {
        const std::string cleaned = trim(line);

        if (cleaned.empty()) {
            continue;
        }

        if (!opened) {
            if (cleaned != "[") {
                throw core::ParseError("Multiline matrix must start with '[' on a separate line");
            }

            opened = true;
            continue;
        }

        if (cleaned == "]") {
            closed = true;
            break;
        }

        std::istringstream rowStream(cleaned);
        std::vector<double> row;
        double value = 0.0;

        while (rowStream >> value) {
            row.push_back(value);
        }

        if (row.empty()) {
            throw core::ParseError("Matrix row does not contain valid numeric values");
        }

        if (!rowStream.eof()) {
            throw core::ParseError("Failed to parse a number in matrix row");
        }

        rows.push_back(std::move(row));
    }

    if (!opened) {
        throw core::ParseError("Matrix input is empty or missing opening '['");
    }

    if (!closed) {
        throw core::ParseError("Matrix input is missing closing ']'");
    }

    while (std::getline(input, line)) {
        if (!trim(line).empty()) {
            throw core::ParseError("Unexpected data after closing ']'");
        }
    }

    return buildMatrix(rows);
}

} // namespace io