#pragma once

#include <string>

namespace uninfer
{
    enum class BackendType
    {
        kMock,
        kTensorRT,
        kOpenVINO,
        kAscend
    };

    enum class TaskType
    {
        kDetection,
        kClassification,
        kPose
    };

    struct ModelConfig
    {
        BackendType backend = BackendType::kMock;
        TaskType task = TaskType::kDetection;
        std::string modelPath;
        int deviceId = 0;
    };

} // namespace uninfer