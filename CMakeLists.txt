cmake_minimum_required(VERSION 3.28.0)

project(Auron VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ./Lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ./Arch)

set(IMGUI_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Auron/External/ImGui")
set(STDIMAGE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Auron/External/STDImage")

# Include Conan toolchain
set(CONAN_TOOLCHAIN_FILE ".conan/conan_toolchain.cmake")
include(${CONAN_TOOLCHAIN_FILE})

find_package(spdlog REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} ./Auron/Source/start.cpp)

# Add source files
file(GLOB_RECURSE SOURCE_FILES "Auron/*.cpp")
file(GLOB_RECURSE HEADER_FILES "Auron/*.h")

target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_FILES} ${HEADER_FILES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE Auron)
target_include_directories(${PROJECT_NAME} PRIVATE "${IMGUI_INCLUDE_DIR}")
target_include_directories(${PROJECT_NAME} PRIVATE "${IMGUI_INCLUDE_DIR}/backends")
target_include_directories(${PROJECT_NAME} PRIVATE "${STDIMAGE_INCLUDE_DIR}")

set_property(TARGET ${PROJECT_NAME} PROPERTY INCLUDE_DIRECTORIES_SYSTEM "${IMGUI_INCLUDE_DIR}")
set_property(TARGET ${PROJECT_NAME} PROPERTY INCLUDE_DIRECTORIES_SYSTEM "${STDIMAGE_INCLUDE_DIR}")

# Link libraries
target_link_libraries(${PROJECT_NAME}
    spdlog::spdlog
    OpenGL::GL
    glfw
    glm::glm
    glad::glad
)