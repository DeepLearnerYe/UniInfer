#pragma once

#include <string>
#include <vector>

#include "uninfer/tensor.hpp"

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

    class IBackend
    {
    public:
        virtual ~IBackend() = default;

        virtual void load(const std::string& model_path) = 0;
        virtual std::vector<Tensor> infer(const std::vector<Tensor>& inputs) = 0;
    };
} // namespace uninfer