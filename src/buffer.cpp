#include "uninfer/buffer.hpp"

#include <stdexcept>

namespace uninfer
{
    Buffer::Buffer(MemoryType memory_type)
    :memory_type_(memory_type)
    {

    }

    MemoryType Buffer::memoryType() const
    {
        return memory_type_;
    }

    std::size_t Buffer::bytes() const
    {
        return host_data_.size();
    }

    bool Buffer::empty() const
    {
        return host_data_.empty();
    }

    void *Buffer::data()
    {
        if(empty())
        {
            return nullptr;
        }
        return host_data_.data();
    }

    const void* Buffer::data() const
    {
        if(empty())
        {
            return nullptr;
        }
        return host_data_.data();
    }

    void Buffer::resize(std::size_t bytes)
    {
        if(memory_type_ != MemoryType::kHost)
        {
            throw std::runtime_error("only host is implemented now");
        }
        host_data_.resize(bytes);
    }

    void Buffer::clear()
    {
        host_data_.clear();
    }
}