#pragma once

#include "report/step.h"

namespace report {

    class PropertyStep final : public Step {
    public:
        enum class Mode {
            Rank,
            Determinant,
            Inverse
        };

        explicit PropertyStep(Mode mode);

        [[nodiscard]] std::string name() const override;
        [[nodiscard]] util::Value run(const core::Matrix& matrix) override;

    private:
        Mode mode_;
    };

}