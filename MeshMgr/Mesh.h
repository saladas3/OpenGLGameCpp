//
// Created by lucai on 10/18/2022.
//

#ifndef OPENGLGAMECPP_MESH_H
#define OPENGLGAMECPP_MESH_H

#include <vector>
#include <string>
#include "../RenderSystem/VAO.h"
#include "../RenderSystem/EBO.h"
#include "../Camera/Camera.h"
#include "../TextureMgr/Texture.h"

class Mesh {
public:
    std::vector<Vertex> vertices{};
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    VAO VAO;

    Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, std::vector<Texture> &textures);

    void Draw(
            Shader &shader,
            Camera &camera,
            glm::mat4 matrix = glm::mat4(1.0f),
            glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
            glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
            glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
    );
};


#endif //OPENGLGAMECPP_MESH_H
