#pragma once

#include <memory>

#include "uninfer/decoder.hpp"
#include "uninfer/backend.hpp"
#include "uninfer/model.hpp"

namespace uninfer
{

    class MockDetectionModel : public IDetectionModel
    {
    public:
        MockDetectionModel();

        DetectionResult predict(const Image &image) override;
    private:
        std::unique_ptr<IBackend> backend_;
        std::unique_ptr<IDecoder<DetectionResult>> decoder_;
    };

} // namespace uninfer