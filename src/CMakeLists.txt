add_executable(Flicker main.cpp glad.c pch.cpp)

target_include_directories(Flicker PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(Flicker PUBLIC ${VENDOR_DIR}/assimp/include)
target_include_directories(Flicker PUBLIC ${VENDOR_DIR}/glfw/include)
target_include_directories(Flicker PUBLIC ${PROJECT_BINARY_DIR}/vendor/assimp/include)
target_include_directories(Flicker PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Flicker PUBLIC assimp glfw)

set_target_properties(Flicker PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "pch.hpp")

set(ASSETS_PATH  ${CMAKE_SOURCE_DIR}/assets)
set(ASSETS_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)

add_definitions(-DASSETS_PATH="assets")

add_custom_command(TARGET Flicker POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        ${ASSETS_OUTPUT_PATH})
add_custom_command(TARGET Flicker POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${ASSETS_PATH} ${ASSETS_OUTPUT_PATH})

add_subdirectory(Application)
add_subdirectory(Assets)
add_subdirectory(Renderer)

cotire(Flicker)