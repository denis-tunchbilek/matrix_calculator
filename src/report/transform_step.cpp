#include "report/transform_step.h"

#include <stdexcept>
#include <string>

#include "core/linalg.h"

namespace report {

    TransformStep::TransformStep(const Mode mode)
        : mode_(mode) {}

    std::string TransformStep::name() const {
        switch (mode_) {
            case Mode::Transpose:
                return "Transpose";
            case Mode::Rref:
                return "RREF";
        }

        return "Transform";
    }

    util::Value TransformStep::run(const core::Matrix& matrix) {
        switch (mode_) {
            case Mode::Transpose:
                return matrix.transpose();
            case Mode::Rref:
                return core::LinAlgService{}.rref(matrix);
        }

        throw std::runtime_error("Unsupported TransformStep mode");
    }

}