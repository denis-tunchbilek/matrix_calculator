#include "report/transform_step.h"

#include <stdexcept>
#include <string>

namespace report {

    TransformStep::TransformStep(const Mode mode)
        : mode_(mode) {}

    std::string TransformStep::name() const {
        switch (mode_) {
            case Mode::Transpose:
                return "Transpose";
        }

        return "Transform";
    }

    util::Value TransformStep::run(const core::Matrix& matrix) {
        switch (mode_) {
            case Mode::Transpose:
                return matrix.transpose();
        }

        throw std::runtime_error("Unsupported TransformStep mode");
    }

}