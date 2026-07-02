cmake_minimum_required(VERSION 3.16)

project(UniInfer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(UNINFER_ENABLE_CUDA "Build UniInfer with CUDA support" OFF)

file(GLOB_RECURSE UNINFER_SOURCES
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

if(NOT UNINFER_ENABLE_CUDA)
    list(FILTER UNINFER_SOURCES EXCLUDE REGEX ".*/cuda_check\\.cpp$")
endif()

if(UNINFER_ENABLE_CUDA)
    find_package(CUDAToolkit REQUIRED)
endif()

add_library(uninfer
    ${UNINFER_SOURCES}
)

target_include_directories(uninfer
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(UNINFER_ENABLE_CUDA)
    target_compile_definitions(uninfer PUBLIC UNINFER_ENABLE_CUDA=1)
    target_link_libraries(uninfer PUBLIC CUDA::cudart)
endif()

add_executable(detect_mock
    examples/detect_mock.cpp
)

target_link_libraries(detect_mock
    PRIVATE
        uninfer
)