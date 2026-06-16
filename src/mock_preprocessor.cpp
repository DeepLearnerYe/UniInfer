#include "uninfer/mock_preprocessor.hpp"

namespace uninfer
{
    Tensor MockPreprocessor::preprocess(const Image& image)
    {
        Tensor input;
        input.name = "image";
        input.dtype = DataType::kFloat32;
        input.shape.dims = {1, image.height, image.width, image.channels};
        input.bytes = static_cast<std::size_t>(image.height) * image.width * image.channels * dataTypeSize(DataType::kFloat32);
        input.data = nullptr;

        return input;
    }
}
