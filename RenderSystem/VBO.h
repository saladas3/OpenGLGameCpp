//
// Created by lucai on 10/16/2022.
//

#ifndef OPENGLGAMECPP_VBO_H
#define OPENGLGAMECPP_VBO_H

#include <vector>
#include "glad/glad.h"
#include "glm.hpp"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 texUV;
};

class VBO {
public:
    // Reference ID of the Vertex Buffer Object
    GLuint ID{};

    // Constructor that generates a Vertex Buffer Object and links it to vertices
    explicit VBO(std::vector<Vertex> &vertices);

    // Binds the VBO
    void Bind() const;

    // Unbinds the VBO
    static void Unbind();

    // Deletes the VBO
    void Delete();
};


#endif //OPENGLGAMECPP_VBO_H
