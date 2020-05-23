cmake_minimum_required(VERSION 3.13)
project(Flicker)

set(CMAKE_CXX_STANDARD 17)
set(BINARIES_DIR ${PROJECT_SOURCE_DIR}/bin)
set(VENDOR_DIR ${PROJECT_SOURCE_DIR}/vendor)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARIES_DIR})

include(cotire)

add_subdirectory(vendor/assimp)
add_subdirectory(vendor/glfw)
add_subdirectory(src)