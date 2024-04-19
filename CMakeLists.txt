cmake_minimum_required(VERSION 3.28.0)

project(AURON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

CMAKE_TOOLCHAIN_FILE(.conan\debug\conan_toolchain.cmake)

add_executable(${PROJECT_NAME} .\Auron\Source\Auron.cpp)