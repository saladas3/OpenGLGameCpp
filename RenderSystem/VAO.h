//
// Created by lucai on 10/16/2022.
//

#ifndef OPENGLGAMECPP_VAO_H
#define OPENGLGAMECPP_VAO_H

#include "glad/glad.h"
#include "VBO.h"

class VAO {
public:
    // ID reference for the Vertex Array Object
    GLuint ID{};

    // Constructor that generates a VAO ID
    VAO();

    // Links a VBO to the VAO using a certain layout
    static void LinkVBO(VBO &VBO, GLuint layout);

    // Binds the VAO
    void Bind() const;

    // Unbinds the VAO
    static void Unbind();

    // Deletes the VAO
    void Delete();
};


#endif //OPENGLGAMECPP_VAO_H
