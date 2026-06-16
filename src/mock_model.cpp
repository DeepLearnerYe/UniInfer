#include "uninfer/mock_model.hpp"
#include "uninfer/mock_backend.hpp"

namespace uninfer
{
    MockDetectionModel::MockDetectionModel()
    :backend_(std::make_unique<MockBackend>())
    {
        backend_->load("");
    }

    DetectionResult MockDetectionModel::predict(const Image& image)
    {
        Tensor input;
        input.name = "image";
        input.dtype = DataType::kFloat32;
        input.shape.dims = {1, image.height, image.width, image.channels};
        input.bytes = image.height * image.width;
        input.data = image.data;

        auto output = backend_->infer({input});
        
        DetectionResult result;

        Detection det;
        det.box.left = image.width * 0.25f;
        det.box.top = image.height * 0.25f;
        det.box.right = image.width * 0.75f;
        det.box.bottom = image.height * 0.75f;
        det.class_id = 0;
        det.score = 0.99f;

        result.detections.push_back(det);
        return result;
    }
}