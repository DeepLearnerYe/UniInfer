#pragma once
#include <cstddef>

namespace uninfer
{

    enum class PixelFormat
    {
        kBGR,
        kRGB,
        kGray,
    };

    struct Image
    {
        void* data = nullptr;
        int width = 0;
        int height = 0;
        int channel = 0;
        std::size_t pitch;
        PixelFormat format = PixelFormat::kBGR;
    };
    
} // namespace uninfer