#pragma once

#include <vector>

#include "uninfer/result.hpp"
#include "uninfer/core.hpp"

namespace uninfer
{

    class IDetectionModel
    {
    public:
        virtual ~IDetectionModel() = default;
        virtual DetectionResult predict(const Image& image) = 0;
        virtual std::vector<DetectionResult> predict(const std::vector<Image>& images) = 0;
    };

}// namespace uninfer