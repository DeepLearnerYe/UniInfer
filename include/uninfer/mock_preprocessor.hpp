#pragma once

#include "uninfer/config.hpp"
#include "uninfer/preprocessor.hpp"

namespace uninfer
{
    class MockPreprocessor : public IPreprocessor
    {
    public:
        explicit MockPreprocessor(const ModelConfig& config);

        Tensor preprocess(const Image& image) override;
        Tensor preprocess(const std::vector<Image>& image) override;
    private:
        int input_width_;
        int input_height_;
    };
} // namespace uninfer
