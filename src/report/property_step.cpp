#include "report/property_step.h"

#include <string>

namespace report {

    PropertyStep::PropertyStep(const Mode mode)
        : mode_(mode) {}

    std::string PropertyStep::name() const {
        switch (mode_) {
            case Mode::Rank:
                return "Rank";
            case Mode::Determinant:
                return "Determinant";
            case Mode::Inverse:
                return "Inverse";
        }

        return "Property";
    }

    util::Value PropertyStep::run(const core::Matrix& matrix) {
        (void)matrix;

        switch (mode_) {
            case Mode::Rank:
                return std::string("rank calculation is not implemented yet");
            case Mode::Determinant:
                return std::string("determinant calculation is not implemented yet");
            case Mode::Inverse:
                return std::string("inverse calculation is not implemented yet");
        }

        return std::string("unknown property step");
    }

}