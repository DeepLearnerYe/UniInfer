#pragma once

#include "uninfer/decoder.hpp"
#include "uninfer/result.hpp"

namespace uninfer
{
    class MockDetectionDecoder : public IDecoder<DetectionResult>
    {
    public:
        DetectionResult decode(const std::vector<Tensor>& outputs) override;
    };
}// namespace uninfer