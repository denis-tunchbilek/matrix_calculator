#include "io/matrix_input.h"

#include "core/errors.h"

namespace io {

    core::Matrix MatrixInput::read(std::istream& input) const {
        (void)input;
        throw core::ParseError("MatrixInput::read is not implemented yet");
    }

} // namespace io