#pragma once

#include <memory>

#include "uninfer/model.hpp"
#include "uninfer/config.hpp"

namespace uninfer
{
    std::unique_ptr<IDetectionModel> createDetectionModel(const ModelConfig& config);
}