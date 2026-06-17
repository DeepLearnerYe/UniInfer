#include "uninfer/mock_model.hpp"
#include "uninfer/mock_backend.hpp"
#include "uninfer/mock_decoder.hpp"
#include "uninfer/mock_preprocessor.hpp"

namespace uninfer
{
    MockDetectionModel::MockDetectionModel(const ModelConfig& config)
    :preprocessor_(std::make_unique<MockPreprocessor>(config)),
    backend_(std::make_unique<MockBackend>()),
    decoder_(std::make_unique<MockDetectionDecoder>())
    {
        backend_->load(config.model_path);
    }

    DetectionResult MockDetectionModel::predict(const Image& image)
    {
        return predict(std::vector<Image>{image}).front();
    }

    std::vector<DetectionResult> MockDetectionModel::predict(const std::vector<Image>& images)
    {
  
        auto input = preprocessor_->preprocess(images);
        auto outputs = backend_->infer({input});
        auto results = decoder_->decode(outputs);

        return results;
    }
}