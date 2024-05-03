cmake_minimum_required(VERSION 3.28.0)

project(Auron VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ./Lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ./Arch)

# Include Conan toolchain
set(CONAN_TOOLCHAIN_FILE ".conan/conan_toolchain.cmake")
include(${CONAN_TOOLCHAIN_FILE})

find_package(spdlog REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} ./Auron/Source/start.cpp)

# Add source files
file(GLOB_RECURSE SOURCE_FILES "Auron/*.cpp")
file(GLOB_RECURSE HEADER_FILES "Auron/*.h")

target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_FILES} ${HEADER_FILES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE Auron)

# Link libraries
target_link_libraries(${PROJECT_NAME}
    spdlog::spdlog
    OpenGL::GL
    glfw
    glad::glad
)