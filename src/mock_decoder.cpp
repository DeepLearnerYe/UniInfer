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

        if(output.dtype != DataType::kFloat32)
        {
            throw std::runtime_error("mock detection output dtype should be float32");
        }

        if(batch <=0 || values_per_image < 6)
        {
            return results;
        }

        if(output.buffer == nullptr)
        {
            throw std::runtime_error("mock detection output is nullptr");
        }

        const auto expected_size = static_cast<std::size_t>(batch) * static_cast<std::size_t>(values_per_image);
        const auto expected_bytes = expected_size * dataTypeSize(output.dtype);
        if(output.bytes < expected_bytes || output.buffer->bytes() < expected_bytes)
        {
            throw std::runtime_error("mock detection output data is incomplete");
        }

        const auto *data = static_cast<const float*>(output.data());
        if(data == nullptr)
        {
            throw std::runtime_error("mock detection output data is nullptr");
        }

        results.reserve(batch);

        for(int i = 0; i < batch; ++i)
        {
            const auto base = static_cast<std::size_t>(i) * static_cast<std::size_t>(values_per_image);

            Detection det;
            det.box.left = data[base + 0];
            det.box.top = data[base + 1];
            det.box.right = data[base + 2];
            det.box.bottom = data[base + 3];
            det.score = data[base + 4];
            det.class_id = static_cast<int>(data[base + 5]);

            DetectionResult result;
            result.detections.push_back(det);
            results.push_back(result);
        }
 
        return results;
    }

}// namespace uninfer