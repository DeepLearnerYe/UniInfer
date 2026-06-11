cmake_minimum_required(VERSION 3.16)

project(Uninfer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(uninfer
    src/mock_model.cpp
)

target_include_directories(uninfer
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(detect_mock
    examples/detect_mock.cpp
)

target_link_libraries(detect_mock
    PRIVATE
        uninfer
)