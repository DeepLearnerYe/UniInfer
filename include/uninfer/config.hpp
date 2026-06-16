#pragma once

#include "uninfer/backend.hpp"
#include "uninfer/task.hpp"

namespace uninfer
{

    struct ModelConfig
    {
        BackendType backend = BackendType::kMock;
        TaskType task = TaskType::kDetection;
        std::string model_path;
        int device_id = 0;
    };

} // namespace uninfer