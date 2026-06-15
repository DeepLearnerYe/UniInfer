#include "uninfer/tensor.hpp"

#include <stdexcept>

namespace uninfer
{
    size_t dataTypeSize(DataType dtype)
    {
        switch (dtype)
        {
        case DataType::kFloat32:
            return 4;
        case DataType::kFloat16:
            return 2;
        case DataType::kInt32:
            return 4;
        case DataType::kInt8:
            return 1;
        default:
            throw std::invalid_argument("unknown data type");
        }
    }
} // namespace uninfer