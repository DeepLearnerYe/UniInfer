#pragma once
#include <vector>

namespace uninfer
{

    struct Box
    {
        float left = 0.0f;
        float top = 0.0f;
        float right = 0.0f;
        float bottom = 0.0f;
    };

    struct Detection
    {
        Box box;
        int class_id = -1;
        float score = 0.0f;
    };

    struct DetectionResult
    {
        std::vector<Detection> detections;
    };
    
}// namespace uninfer
