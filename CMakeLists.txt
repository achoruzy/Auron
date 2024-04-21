# Copyright (C) Auron Project by Arkadiusz Choruzy
# All rights reserved.

cmake_minimum_required(VERSION 3.28.0)

project(Auron VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ./Lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ./Arch)

set(CMAKE_TOOLCHAIN_FILE .conan/debug/conan_toolchain.cmake)

add_executable(${PROJECT_NAME} ./Auron/Source/start.cpp)