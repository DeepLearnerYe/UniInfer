#include "uninfer/buffer.hpp"


namespace uninfer
{

    MemoryType HostBuffer::memoryType() const
    {
        return MemoryType::kHost;
    }

    std::size_t HostBuffer::bytes() const
    {
        return host_data_.size();
    }

    bool HostBuffer::empty() const
    {
        return host_data_.empty();
    }

    void *HostBuffer::data()
    {
        if(empty())
        {
            return nullptr;
        }
        return host_data_.data();
    }

    const void* HostBuffer::data() const
    {
        if(empty())
        {
            return nullptr;
        }
        return host_data_.data();
    }

    void HostBuffer::resize(std::size_t bytes)
    {
        host_data_.resize(bytes);
    }

    void HostBuffer::clear()
    {
        host_data_.clear();
    }
}