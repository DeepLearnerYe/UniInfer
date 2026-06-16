#include "uninfer/mock_backend.hpp"

namespace uninfer
{
    void MockBackend::load(const std::string& model_path)
    {
        (void)model_path;
    }

    std::vector<Tensor> MockBackend::infer(const std::vector<Tensor>& inputs)
    {
        (void)inputs;

        Tensor output;
        output.name = "mock_output";
        output.dtype = DataType::kFloat32;
        output.shape.dims = {1, 6};
        output.bytes = 6 * dataTypeSize(output.dtype);
        output.data = nullptr;

        return {output};
    }
}