#pragma once

#include "uninfer/buffer.hpp"

#include <cstddef>
#include <string>
#include <vector>
#include <memory>


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

        int rank() const;
        bool empty() const;
        std::size_t elementCount() const;
    };

    struct Tensor
    {
        std::string name;
        DataType dtype = DataType::kFloat32;
        TensorShape shape;
        std::size_t bytes = 0;
        std::shared_ptr<IBuffer> buffer;

        void *data();
        const void* data() const;
        bool empty() const;
        std::size_t elementCount() const;
        std::size_t computeBytes() const;
        void refreshBytes();
    };

    std::size_t dataTypeSize(DataType dtype);

} // namespace uninfer