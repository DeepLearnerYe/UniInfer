#include "uninfer/mock_backend.hpp"

namespace uninfer
{
    void MockBackend::load(const std::string& model_path)
    {
        (void)model_path;
    }

    std::vector<Tensor> MockBackend::infer(const std::vector<Tensor>& inputs)
    {
        if (inputs.empty() || inputs[0].shape.dims.empty())
        {
            return {};
        }
        const int batch = inputs[0].shape.dims[0];
        if(batch <= 0)
        {
            return {};
        }

        Tensor output;
        output.name = "mock_output";
        output.dtype = DataType::kFloat32;
        output.shape.dims = {batch, 6};
        output.refreshBytes();
        output.host_data.reserve(static_cast<std::size_t>(batch) * 6);

        for(int i = 0; i < batch; ++i)
        {
            output.host_data.push_back(160.0f);
            output.host_data.push_back(120.0f);
            output.host_data.push_back(480.0f);
            output.host_data.push_back(360.0f);
            output.host_data.push_back(0.99f);
            output.host_data.push_back(0.0f);
        }
        
        output.data = output.host_data.data();

        return {output};
    }
}