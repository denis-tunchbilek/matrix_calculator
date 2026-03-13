#include "io/matrix_input.h"

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "core/errors.h"

namespace matrix::io {
namespace {

using matrix::core::Matrix;
using matrix::core::ParseError;

std::string trim(const std::string& text) {
    std::size_t start = 0;
    while (start < text.size() && std::isspace(static_cast<unsigned char>(text[start])) != 0) {
        ++start;
    }

    std::size_t end = text.size();
    while (end > start && std::isspace(static_cast<unsigned char>(text[end - 1])) != 0) {
        --end;
    }
    return text.substr(start, end - start);
}

Matrix buildMatrix(const std::vector<std::vector<double>>& rows) {
    if (rows.empty()) {
        throw ParseError("matrix is empty");
    }
    const auto width = static_cast<int>(rows.front().size());
    if (width == 0) {
        throw ParseError("matrix row is empty");
    }

    Matrix matrix(static_cast<int>(rows.size()), width);
    for (int r = 0; r < matrix.rows(); ++r) {
        if (static_cast<int>(rows[static_cast<std::size_t>(r)].size()) != width) {
            throw ParseError("all rows must have the same number of elements");
        }
        for (int c = 0; c < width; ++c) {
            matrix.at(r, c) = rows[static_cast<std::size_t>(r)][static_cast<std::size_t>(c)];
        }
    }
    return matrix;
}

Matrix parseMultiline(const std::vector<std::string>& lines) {
    std::vector<std::vector<double>> rows;
    for (const std::string& line : lines) {
        const std::string current = trim(line);
        if (current.empty() || current == "[" || current == "]") {
            continue;
        }
        std::istringstream rowStream(current);
        std::vector<double> row;
        double value = 0.0;
        while (rowStream >> value) {
            row.push_back(value);
        }
        if (row.empty()) {
            throw ParseError("cannot parse row: '" + current + "'");
        }
        if (!rowStream.eof()) {
            throw ParseError("unexpected token in row: '" + current + "'");
        }
        rows.push_back(row);
    }
    return buildMatrix(rows);
}

Matrix parseSingleLine(const std::string& text) {
    if (text.size() < 4 || text.front() != '[' || text.back() != ']') {
        throw ParseError("single-line matrix must look like [[1,2],[3,4]]");
    }

    std::vector<std::vector<double>> rows;
    std::size_t pos = 0;

    auto skipSpaces = [&]() {
        while (pos < text.size() && std::isspace(static_cast<unsigned char>(text[pos])) != 0) {
            ++pos;
        }
    };

    auto expect = [&](const char ch, const std::string& what) {
        skipSpaces();
        if (pos >= text.size() || text[pos] != ch) {
            throw ParseError("expected " + what);
        }
        ++pos;
    };

    expect('[', "'[' at matrix start");
    skipSpaces();
    while (pos < text.size() && text[pos] == '[') {
        expect('[', "'[' at row start");
        std::vector<double> row;
        while (true) {
            skipSpaces();
            std::size_t consumed = 0;
            const std::string tail = text.substr(pos);
            double value = 0.0;
            try {
                value = std::stod(tail, &consumed);
            } catch (...) {
                throw ParseError("expected number in single-line matrix");
            }
            row.push_back(value);
            pos += consumed;
            skipSpaces();
            if (pos < text.size() && text[pos] == ',') {
                ++pos;
                continue;
            }
            break;
        }
        expect(']', "']' at row end");
        rows.push_back(row);
        skipSpaces();
        if (pos < text.size() && text[pos] == ',') {
            ++pos;
            skipSpaces();
            continue;
        }
        break;
    }
    expect(']', "']' at matrix end");
    skipSpaces();
    if (pos != text.size()) {
        throw ParseError("unexpected trailing characters after matrix");
    }
    return buildMatrix(rows);
}

} // namespace

Matrix MatrixInput::read(std::istream& in) const {
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(in, line)) {
        if (!trim(line).empty()) {
            lines.push_back(line);
        }
    }

    if (lines.empty()) {
        throw ParseError("input is empty");
    }

    if (lines.size() == 1) {
        const std::string oneLine = trim(lines.front());
        if (oneLine.find(',') != std::string::npos || oneLine.find("[[") == 0) {
            return parseSingleLine(oneLine);
        }
    }

    return parseMultiline(lines);
}

} // namespace matrix::io