#pragma once


#include "uninfer/tensor.hpp"
#include "uninfer/core.hpp"

namespace uninfer
{
    class IPreprocessor
    {
    public:
        virtual ~IPreprocessor() = default;

        virtual Tensor preprocess(const Image& image) = 0;
    };
}// namespace uninfer