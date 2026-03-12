#pragma once

#include "report/step.h"

namespace report {

    class TransformStep final : public Step {
    public:
        enum class Mode {
            Transpose
        };

        explicit TransformStep(Mode mode);

        [[nodiscard]] std::string name() const override;
        [[nodiscard]] util::Value run(const core::Matrix& matrix) override;

    private:
        Mode mode_;
    };

}