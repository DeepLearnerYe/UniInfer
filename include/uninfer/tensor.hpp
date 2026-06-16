#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace uninfer
{
    enum class DataType
    {
        kFloat32,
        kFloat16,
        kInt32,
        kInt8
    };

    struct TensorShape
    {
        std::vector<int> dims;
    };

    struct Tensor
    {
        std::string name;
        DataType dtype = DataType::kFloat32;
        TensorShape shape;
        void* data = nullptr;
        std::size_t bytes = 0;
    };

    std::size_t dataTypeSize(DataType dtype);

} // namespace uninfer