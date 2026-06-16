#pragma once

#include "uninfer/backend.hpp"

namespace uninfer
{
    class MockBackend : public IBackend
    {
        void load(const std::string& model_path) override;
        std::vector<Tensor> infer(const std::vector<Tensor>& inputs) override;
    };
} // namespace uninfer