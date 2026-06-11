#pragma once
#include <cstddef>

namespace uninfer
{

    enum class PixelFormat
    {
        kBGR,
        kRGB,
        kGRAY,
    };

    struct Image
    {
        void* data = nullptr;
        int width = 0;
        int height = 0;
        int channel = 0;
        std::size_t pitch = 0;
        PixelFormat format = PixelFormat::kBGR;
    };
    
} // namespace uninfer