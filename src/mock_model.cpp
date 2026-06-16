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
        input.bytes = image.height * image.width * image.channels * dataTypeSize(DataType::kFloat32);
        input.data = nullptr;

        auto outputs = backend_->infer({input});
        
        DetectionResult result;
        if(outputs.empty() || outputs[0].host_data.size() < 6)
        {
            return result;
        }

        const auto &values = outputs[0].host_data;

        Detection det;
        det.box.left = values[0];
        det.box.top = values[1];
        det.box.right = values[2];
        det.box.bottom = values[3];
        det.score = values[4];
        det.class_id = static_cast<int>(values[5]);

        result.detections.push_back(det);
        return result;
    }
}