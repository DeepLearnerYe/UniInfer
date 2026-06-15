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

    std::string toString(BackendType type);
}// namespace uninfer