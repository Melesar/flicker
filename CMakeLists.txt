cmake_minimum_required(VERSION 3.13)
project(Flicker)

set(CMAKE_CXX_STANDARD 17)
set(VENDOR_DIR ${PROJECT_SOURCE_DIR}/vendor)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")
set(BINARIES_DIR ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

include(cotire)

add_subdirectory(vendor/assimp)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/ecs)
add_subdirectory(src)