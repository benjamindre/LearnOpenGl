cmake_minimum_required(VERSION 3.26)

project(LearnOpenGl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

include_directories(include)

add_subdirectory(external/glad)
add_subdirectory(external/glfw)
add_subdirectory(external/glm)
add_subdirectory(external/imgui)
add_subdirectory(external/stb)
add_subdirectory(external/assimp)

add_subdirectory(src)
add_subdirectory(examples/chapter2)
add_subdirectory(examples/chapter3)


message(STATUS "Cmake Build Type: ${CMAKE_BUILD_TYPE}")