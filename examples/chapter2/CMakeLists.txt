project(chapter2)

add_executable(${PROJECT_NAME} main.cpp ChapterLayer.cpp)
target_link_libraries(${PROJECT_NAME} opengl_learn_lib)