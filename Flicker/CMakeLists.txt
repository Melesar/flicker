add_executable(Flicker main.cpp glad.c pch.hpp pch.cpp)

target_include_directories(Flicker PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(Flicker PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_library(LIB_ASSIMP NAMES assimp PATHS ${LIB_DIR})
find_library(LIB_GLFW NAMES glfw3 glfw3dll PATHS ${LIB_DIR})

target_link_libraries(Flicker PUBLIC  ${LIB_ASSIMP})
target_link_libraries(Flicker PUBLIC  ${LIB_GLFW})

set_target_properties(Flicker PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "pch.hpp")

file(COPY ${LIB_DIR}/assimp.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${LIB_DIR}/glfw3.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

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
add_subdirectory(Renderer)
add_subdirectory(Shader)
add_subdirectory(Assets)
add_subdirectory(Models)
add_subdirectory(Scene)
add_subdirectory(Material)
add_subdirectory(Light)
add_subdirectory(Utils)
add_subdirectory(tests)

cotire(Flicker)