add_library(ecs STATIC free_list.cpp)

target_include_directories(ecs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(LIBRARY_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})