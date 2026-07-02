#pragma once

#ifdef UNINFER_ENABLE_CUDA

#include <cuda_runtime_api.h>


namespace uninfer
{
    void cudaCheck(cudaError_t error, const char* file, int line, const char* expr);
}

#define UNINFER_CUDA_CHECK(expr) \
    ::uninfer::cudaCheck((expr), __FILE__, __LINE__, #expr)

#endif