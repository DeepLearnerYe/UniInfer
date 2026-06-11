#include "uninfer/mock_model.hpp"

namespace uninfer
{
    DetectionResult MockDetectionModel::predict(const Image& image)
    {
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