#include "uninfer/cuda_check.hpp"

#include <stdexcept>
#include <string>

namespace uninfer
{
    void cudaCheck(cudaError_t error, const char* file, int line, const char* expr)
    {
        if(error == cudaSuccess)
        {
            return;
        }

        std::string message = "CUDA error: ";
        message += cudaGetErrorString(error);
        message += " at ";
        message += file;
        message += " : ";
        message += std::to_string(line);
        message += " expression: ";
        message += expr;

        throw std::runtime_error(message);
    }
}