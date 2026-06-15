#include "uninfer/factory.hpp"

#include <stdexcept>

#include "uninfer/mock_model.hpp"

namespace uninfer
{
    std::unique_ptr<IDetectionModel> createDetectionModel(const ModelConfig &config)
    {
        if (config.task != TaskType::kDetection)
        {
            throw std::invalid_argument("createDetectionModel requires detection task");
        }

        switch (config.backend)
        {
        case BackendType::kMock:
            return std::make_unique<MockDetectionModel>();
        case BackendType::kTensorRT:
            throw std::runtime_error("TensorRT backend is not implemented yet");
        case BackendType::kOpenVINO:
            throw std::runtime_error("OpenVINO backend is not implemented yet");
        case BackendType::kAscend:
            throw std::runtime_error("Ascend backend is not implemented yet");
        default:
            throw std::runtime_error("unknown backend type");
        }
    }
} // namespace uninfer