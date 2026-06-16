#include <iostream>
#include "uninfer/core.hpp"
#include "uninfer/config.hpp"
#include "uninfer/factory.hpp"

int main()
{
    uninfer::Image image;
    image.width = 640;
    image.height = 480;
    image.channels = 3;
    image.pitch = image.width * image.channels;
    image.format = uninfer::PixelFormat::kBGR;

    uninfer::ModelConfig config;
    config.backend = uninfer::BackendType::kMock;
    config.task = uninfer::TaskType::kDetection;
    config.model_path = "mock.engine";
    auto model = uninfer::createDetectionModel(config);
    auto result = model->predict(image);
    std::cout << "backend = " << uninfer::toString(config.backend) << std::endl;

    for(const auto& det: result.detections)
    {
        std::cout << "class_id = " << det.class_id
                << ", score = " << det.score
                << ", box = (" << det.box.left << ", "
                << det.box.top << ", "
                << det.box.right << ", "
                << det.box.bottom << ") " << std::endl;
    }
}