cmake_minimum_required(VERSION 3.16)
project(mandelbrot_sfml VERSION 0.1.0)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(mandelbrot_sfml main.cpp)
target_compile_options(mandelbrot_sfml PRIVATE -Wall -Wextra -fsanitize=address)
target_link_libraries(mandelbrot_sfml PRIVATE sfml-graphics)
target_link_options(mandelbrot_sfml PRIVATE -fsanitize=address)