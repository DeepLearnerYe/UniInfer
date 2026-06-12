#pragma once
#include "uninfer/model.hpp"

namespace uninfer
{

    class MockDetectionModel : public IDetectionModel
    {
    public:
        DetectionResult predict(const Image &image) override;
    };

} // namespace uninfer