#include "uninfer/tensor.hpp"

#include <limits>
#include <stdexcept>

namespace uninfer
{
    std::size_t dataTypeSize(DataType dtype)
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

    int TensorShape::rank() const
    {
        return static_cast<int>(dims.size());
    }

    bool TensorShape::empty() const
    {
        return dims.empty();
    }

    std::size_t TensorShape::elementCount() const
    {
        if(dims.empty())
        {
            return 0;
        }

        std::size_t count = 1;

        for(int dim: dims)
        {
            if(dim < 0)
            {
                throw std::invalid_argument("tensor shape contains negative dim");
            }

            if(dim == 0)
            {
                return 0;
            }

            const auto value = static_cast<std::size_t>(dim);
            if(count > std::numeric_limits<std::size_t>::max() / value )
            {
                throw std::overflow_error("tensor element count overflow");
            }

            count *= value;
        }

        return count;
    }

    void *Tensor::data()
    {
        if(buffer == nullptr)
        {
            return nullptr;
        }

        return buffer->data();
    }

    const void *Tensor::data() const
    {
        if(buffer == nullptr)
        {
            return nullptr;
        }

        return buffer->data();
    }

    bool Tensor::empty() const
    { 
        return elementCount() == 0;
    }

    std::size_t Tensor::elementCount() const
    {
        return shape.elementCount();
    }

    std::size_t Tensor::computeBytes() const
    {
        const auto count = elementCount();
        const auto size = dataTypeSize(dtype);

        if( count > std::numeric_limits<std::size_t>::max() / size)
        {
            throw std::overflow_error("tensor byte size overflow");
        }

        return count * size;
    }

    void Tensor::refreshBytes()
    {
        bytes = computeBytes();
    }

} // namespace uninfer