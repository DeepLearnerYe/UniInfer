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
        int input_width = 0;
        int input_height = 0;
        int device_id = 0;
    };

} // namespace uninfer