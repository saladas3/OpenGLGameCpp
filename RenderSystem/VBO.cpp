//
// Created by lucai on 10/16/2022.
//

#include "VBO.h"

// Constructor that generates a Vertex Buffer Object and links it to vertices
VBO::VBO(std::vector<Vertex> &vertices) {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER,
                 vertices.size() * sizeof(Vertex), // NOLINT(cppcoreguidelines-narrowing-conversions)
                 vertices.data(),
                 GL_STATIC_DRAW);
}

// Binds the VBO
void VBO::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Unbinds the VBO
void VBO::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Deletes the VBO
void VBO::Delete() {
    glDeleteBuffers(1, &ID);
}
