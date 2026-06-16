#pragma once

#include "uninfer/preprocessor.hpp"

namespace uninfer
{
    class MockPreprocessor : public IPreprocessor
    {
    public:
        Tensor preprocess(const Image& image) override;
    };
} // namespace uninfer
