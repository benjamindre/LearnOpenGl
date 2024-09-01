project(chapter3)

add_executable(${PROJECT_NAME} main.cpp ModelLayer.cpp)
target_link_libraries(${PROJECT_NAME} opengl_learn_lib)