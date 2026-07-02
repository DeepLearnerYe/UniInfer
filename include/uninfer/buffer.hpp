#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace uninfer
{
    enum class MemoryType
    {
        kHost,
        kDevice,
        kPinnedHost,
        kUnified
    };

    class IBuffer
    {
    public:
        IBuffer() = default;

        IBuffer(const IBuffer& ) = delete;
        IBuffer& operator=(const IBuffer& ) = delete;

        IBuffer(IBuffer&& ) noexcept = default;
        IBuffer& operator=(IBuffer&& ) noexcept = default;

        virtual ~IBuffer() = default;

        virtual MemoryType memoryType() const = 0;
        virtual std::size_t bytes() const = 0;
        virtual bool empty() const = 0;

        virtual void *data() = 0;
        virtual const void* data() const = 0;

        virtual void resize(std::size_t bytes) = 0;
        virtual void clear() = 0;
    };

    class HostBuffer : public IBuffer
    {
    public:
        HostBuffer() = default;

        MemoryType memoryType() const override;
        std::size_t bytes() const override;
        bool empty() const override;

        void *data() override;
        const void* data() const override;

        void resize(std::size_t bytes) override;
        void clear() override;
        
    private:
        std::vector<std::uint8_t> host_data_;
    };
} // namespace uninfer