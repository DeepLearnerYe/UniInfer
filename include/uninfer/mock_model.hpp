#pragma once

#include <memory>

#include "uninfer/model.hpp"
#include "uninfer/backend.hpp"

namespace uninfer
{

    class MockDetectionModel : public IDetectionModel
    {
    public:
        MockDetectionModel();

        DetectionResult predict(const Image &image) override;
    private:
        std::unique_ptr<IBackend> backend_;
    };

} // namespace uninfer