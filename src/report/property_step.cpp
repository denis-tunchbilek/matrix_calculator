#include "report/property_step.h"

#include <string>

#include "core/errors.h"
#include "core/linalg.h"

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
        core::LinAlgService service;

        switch (mode_) {
            case Mode::Rank:
                return service.rank(matrix);

            case Mode::Determinant:
                try {
                    return service.det(matrix);
                } catch (const core::DimensionError&) {
                    return std::string("determinant is defined only for square matrices");
                }

            case Mode::Inverse:
                try {
                    const auto inverse = service.inverse(matrix);
                    if (inverse.has_value()) {
                        return *inverse;
                    }
                    return std::string("inverse does not exist for a singular matrix");
                } catch (const core::DimensionError&) {
                    return std::string("inverse is defined only for square matrices");
                }
        }

        return std::string("unknown property step");
    }

}