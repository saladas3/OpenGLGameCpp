//
// Created by lucai on 10/16/2022.
//

#include "EBO.h"

// Constructor that generates an Elements Buffer Object and links it to indices
EBO::EBO(std::vector<GLuint> &indices) {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indices.size() * sizeof(GLuint), // NOLINT(cppcoreguidelines-narrowing-conversions)
                 indices.data(),
                 GL_STATIC_DRAW);
}

// Binds the EBO
void EBO::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// Unbinds the EBO
void EBO::Unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Deletes the EBO
void EBO::Delete() {
    glDeleteBuffers(1, &ID);
}
