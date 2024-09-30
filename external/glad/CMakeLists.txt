set(PROJECT_NAME glad)

set(GLAD_SOURCES
    src/glad.c
)

add_library(${PROJECT_NAME} ${GLAD_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)