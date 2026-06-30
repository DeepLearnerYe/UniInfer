#include <stdexcept>

#include "uninfer/mock_preprocessor.hpp"

namespace uninfer
{
    MockPreprocessor::MockPreprocessor(const ModelConfig &config)
        : input_width_(config.input_width), input_height_(config.input_height)
    {
        if (input_width_ <= 0 || input_height_ <= 0)
        {
            throw std::invalid_argument("input size must be positive");
        }
    }

    Tensor MockPreprocessor::preprocess(const Image &image)
    {
        return preprocess(std::vector<Image>{image});
    }

    Tensor MockPreprocessor::preprocess(const std::vector<Image>& images)
    {
        if(images.empty())
        {
            throw std::invalid_argument("images must not be empty");
        }
        for(const auto& image : images)
        {
            if (image.width <= 0 || image.height <= 0 || image.channels <= 0)
            {
                throw std::invalid_argument("image shape must be positive");
            }
        }
        
        const int batch = static_cast<int>(images.size());

        Tensor input;
        input.name = "image";
        input.dtype = DataType::kFloat32;
        input.shape.dims = {batch, 3, input_height_, input_width_};
        input.refreshBytes();
        input.data = nullptr;

        return input;
    }
}
