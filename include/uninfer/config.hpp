#pragma once

#include "uninfer/backend.hpp"

namespace uninfer
{

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
        std::string model_path;
        int device_id = 0;
    };

} // namespace uninfer