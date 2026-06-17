#pragma once

#include <memory>
#include <vector>

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
        std::vector<DetectionResult> predict(const std::vector<Image>& images) override;
    private:
        std::unique_ptr<IPreprocessor> preprocessor_;
        std::unique_ptr<IBackend> backend_;
        std::unique_ptr<IDecoder<std::vector<DetectionResult>>> decoder_;
    };

} // namespace uninfer