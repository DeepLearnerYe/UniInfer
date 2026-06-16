#include "uninfer/mock_model.hpp"
#include "uninfer/mock_backend.hpp"
#include "uninfer/mock_decoder.hpp"
#include "uninfer/mock_preprocessor.hpp"

namespace uninfer
{
    MockDetectionModel::MockDetectionModel(const ModelConfig& config)
    :preprocessor_(std::make_unique<MockPreprocessor>()),
    backend_(std::make_unique<MockBackend>()),
    decoder_(std::make_unique<MockDetectionDecoder>())
    {
        backend_->load(config.model_path);
    }

    DetectionResult MockDetectionModel::predict(const Image& image)
    {
        auto input = preprocessor_->preprocess(image);
        auto outputs = backend_->infer({input});
        auto result = decoder_->decode(outputs);
  
        return result;
    }
}