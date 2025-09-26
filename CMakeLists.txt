cmake_minimum_required(VERSION 4.0)
project(project_1_image_processing)

set(CMAKE_CXX_STANDARD 20)

add_executable(project_1_image_processing
        src/main.cpp
        src/TgaContainer.cpp
        src/TgaContainer.hpp
        src/Pixel.cpp
        src/Pixel.hpp
)
