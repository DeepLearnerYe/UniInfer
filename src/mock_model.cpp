#include "uninfer/mock_model.hpp"
#include "uninfer/mock_backend.hpp"
#include "uninfer/mock_decoder.hpp"

namespace uninfer
{
    MockDetectionModel::MockDetectionModel()
    :backend_(std::make_unique<MockBackend>()),
    decoder_(std::make_unique<MockDetectionDecoder>())
    {
        backend_->load("");
    }

    DetectionResult MockDetectionModel::predict(const Image& image)
    {
        Tensor input;
        input.name = "image";
        input.dtype = DataType::kFloat32;
        input.shape.dims = {1, image.height, image.width, image.channels};
        input.bytes = image.height * image.width * image.channels * dataTypeSize(DataType::kFloat32);
        input.data = nullptr;

        auto outputs = backend_->infer({input});
        auto result = decoder_->decode(outputs);
  
        return result;
    }
}