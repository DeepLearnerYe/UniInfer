#pragma once

#include <vector>

#include "uninfer/tensor.hpp"
#include "uninfer/core.hpp"

namespace uninfer
{
    class IPreprocessor
    {
    public:
        virtual ~IPreprocessor() = default;

        virtual Tensor preprocess(const Image& image) = 0;
        virtual Tensor preprocess(const std::vector<Image>& images) = 0;
    };
}// namespace uninfer