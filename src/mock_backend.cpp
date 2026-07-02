#include "uninfer/mock_backend.hpp"

#include <memory>

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
        output.buffer = std::make_shared<HostBuffer>();
        output.buffer->resize(output.bytes);

        auto *data = static_cast<float*>(output.data()); 
        for(int i = 0; i < batch; ++i)
        {
            const auto base = static_cast<std::size_t>(i) * 6;
            data[base + 0] = 160.0f;
            data[base + 1] = 120.0f;
            data[base + 2] = 480.0f;
            data[base + 3] = 360.0f;
            data[base + 4] = 0.99f;
            data[base + 5] = 0.0f;
        }

        return {output};
    }
}