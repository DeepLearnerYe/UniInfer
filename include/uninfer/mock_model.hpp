#pragma once

#include <memory>

#include "uninfer/config.hpp"
#include "uninfer/backend.hpp"
#include "uninfer/decoder.hpp"
#include "uninfer/model.hpp"
#include "uninfer/preprocessor.hpp"

namespace uninfer
{

    class MockDetectionModel : public IDetectionModel
    {
    public:
        explicit MockDetectionModel(const ModelConfig& config);

        DetectionResult predict(const Image &image) override;
    private:
        std::unique_ptr<IPreprocessor> preprocessor_;
        std::unique_ptr<IBackend> backend_;
        std::unique_ptr<IDecoder<DetectionResult>> decoder_;
    };

} // namespace uninfer