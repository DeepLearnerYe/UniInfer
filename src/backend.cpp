#include "uninfer/backend.hpp"

#include <stdexcept>

namespace uninfer
{
    std::string toString(BackendType type)
    {
        switch (type)
        {
        case BackendType::kMock:
            return "Mock";
        case BackendType::kTensorRT:
            return "TensorRT";
        case BackendType::kOpenVINO:
            return "OpenVINO";
        case BackendType::kAscend:
            return "Ascend";
        default:
            throw std::invalid_argument("unknown backend type");
        }
    }
} // namespace uninfer
