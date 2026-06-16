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
        output.host_data = {160.0f, 120.0f, 480.0f, 360.0f, 0.99f, 0.0f};
        output.bytes = output.host_data.size() * dataTypeSize(output.dtype);
        output.data = output.host_data.data();

        return {output};
    }
}