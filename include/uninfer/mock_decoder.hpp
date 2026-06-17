#pragma once

#include <vector>

#include "uninfer/decoder.hpp"
#include "uninfer/result.hpp"

namespace uninfer
{
    class MockDetectionDecoder : public IDecoder<std::vector<DetectionResult>>
    {
    public:
        std::vector<DetectionResult> decode(const std::vector<Tensor>& outputs) override;
    };
}// namespace uninfer