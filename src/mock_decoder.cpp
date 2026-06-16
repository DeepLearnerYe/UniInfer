#include "uninfer/mock_decoder.hpp"

namespace uninfer
{

    DetectionResult MockDetectionDecoder::decode(const std::vector<Tensor>& outputs)
    {
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

}// namespace uninfer