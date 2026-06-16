#include "uninfer/mock_backend.hpp"

namespace uninfer
{
    void MockBackend::load(const std::string& model_path)
    {
        return;
    }

    std::vector<Tensor> infer(const std::vector<Tensor>& inputs)
    {
        (void)inputs;

        Tensor output;
        output.name = "mock_output";
        output.dtype = DataType::kFloat16;
        output.shape.dims = {1, 6};
        output.bytes = 6 * dataTypeSize(output.dtype);
        output.data = nullptr;

        return {output};
    }
}