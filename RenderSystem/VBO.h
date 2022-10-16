//
// Created by lucai on 10/16/2022.
//

#ifndef OPENGLGAMECPP_VBO_H
#define OPENGLGAMECPP_VBO_H

#include "glad/glad.h"

class VBO {
public:
    // Reference ID of the Vertex Buffer Object
    GLuint ID{};

    // Constructor that generates a Vertex Buffer Object and links it to vertices
    VBO(GLfloat *vertices, GLsizeiptr size);

    // Binds the VBO
    void Bind() const;

    // Unbinds the VBO
    static void Unbind();

    // Deletes the VBO
    void Delete();
};


#endif //OPENGLGAMECPP_VBO_H
