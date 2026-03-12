#include <iostream>
#include <sstream>
#include <string>

#include "core/errors.h"

namespace {

    [[nodiscard]] std::string readAllStdin() {
        std::ostringstream buffer;
        buffer << std::cin.rdbuf();
        return buffer.str();
    }

} // namespace

int main() {
    try {
        const std::string inputText = readAllStdin();

        if (!inputText.empty()) {
            std::cout << "Input received (" << inputText.size()
                      << " chars). Parsing pipeline is not assembled yet.\n";
        } else {
            std::cout << "No stdin input provided. Application pipeline is not assembled yet.\n";
        }

        return 0;
    } catch (const core::MatrixError& error) {
        std::cerr << "Matrix error: " << error.what() << '\n';
        return 1;
    } catch (const std::exception& error) {
        std::cerr << "Unexpected error: " << error.what() << '\n';
        return 1;
    }
}