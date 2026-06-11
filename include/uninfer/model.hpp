#pragma once
#include "uninfer/result.hpp"
#include "uninfer/core.hpp"

namespace uninfer
{

    class IDetectionModel
    {
    public:
        virtual ~IDetectionModel() = default;
        virtual DetectionResult predict(const Image& image) = 0;
    };

}// namespace uninfer