#include "uninfer/mock_decoder.hpp"

#include <stdexcept>

namespace uninfer
{

    std::vector<DetectionResult> MockDetectionDecoder::decode(const std::vector<Tensor>& outputs)
    {
        std::vector<DetectionResult> results;
        if(outputs.empty())
        {
            return results;
        }

        const auto& output = outputs[0];
        if(output.shape.rank() !=2 || output.shape.dims[1] != 6)
        {
            throw std::runtime_error("mock detection output shape should be [N, 6]");
        }
        const int batch = output.shape.dims[0];
        const int values_per_image = output.shape.dims[1];

        if(batch <=0 || values_per_image < 6)
        {
            return results;
        }

        const auto expected_size = static_cast<std::size_t>(batch) * static_cast<std::size_t>(values_per_image);
        if(output.host_data.size() < expected_size)
        {
            throw std::runtime_error("mock detection output data is incomplete");
        }

        results.reserve(batch);

        for(int i = 0; i < batch; ++i)
        {
            const auto base = static_cast<std::size_t>(i) * static_cast<std::size_t>(values_per_image);

            Detection det;
            det.box.left = output.host_data[base + 0];
            det.box.top = output.host_data[base + 1];
            det.box.right = output.host_data[base + 2];
            det.box.bottom = output.host_data[base + 3];
            det.score = output.host_data[base + 4];
            det.class_id = static_cast<int>(output.host_data[base + 5]);

            DetectionResult result;
            result.detections.push_back(det);
            results.push_back(result);
        }
 
        return results;
    }

}// namespace uninfer