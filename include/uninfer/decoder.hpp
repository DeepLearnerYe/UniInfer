#pragma once

#include <vector>

#include "uninfer/tensor.hpp"

namespace uninfer
{
    template <typename ResultType>
    class IDecoder
    {
    public:
        virtual ~IDecoder() = default;

        virtual ResultType decode(const std::vector<Tensor>& outputs) = 0;
    };
}// namespace uninfer