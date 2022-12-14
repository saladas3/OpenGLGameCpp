cmake_minimum_required(VERSION 3.23)
project(OpenGLGameCpp)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(glfw)
add_subdirectory(glm)

add_executable(${CMAKE_PROJECT_NAME}
        glad.c
        stb.cpp
        json/json.h
        main.cpp
        Window/MainWindow.cpp Window/MainWindow.h
        ShaderMgr/Shader.cpp ShaderMgr/Shader.h
        RenderSystem/VAO.cpp RenderSystem/VAO.h
        RenderSystem/VBO.cpp RenderSystem/VBO.h
        RenderSystem/EBO.cpp RenderSystem/EBO.h
        TextureMgr/Texture.cpp TextureMgr/Texture.h
        Camera/Camera.cpp Camera/Camera.h
        MeshMgr/Mesh.cpp MeshMgr/Mesh.h MeshMgr/Model.cpp MeshMgr/Model.h)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glm/glm)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/json)

target_link_libraries(${CMAKE_PROJECT_NAME}
        glfw
        glm)
