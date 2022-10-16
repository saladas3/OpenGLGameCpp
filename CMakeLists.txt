cmake_minimum_required(VERSION 3.23)
project(OpenGLGameCpp)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(glfw)
add_subdirectory(glm)

add_executable(${CMAKE_PROJECT_NAME}
        glad.c
        main.cpp
        MainWindow.cpp
        MainWindow.h
        Shaders/InCodeShaders.h)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glm/glm)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad)

target_link_libraries(${CMAKE_PROJECT_NAME}
        glfw
        glm
        )
