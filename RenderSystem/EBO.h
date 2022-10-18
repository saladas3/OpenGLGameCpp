//
// Created by lucai on 10/16/2022.
//

#ifndef OPENGLGAMECPP_EBO_H
#define OPENGLGAMECPP_EBO_H

#include<glad/glad.h>
#include <vector>

class EBO {
public:
    // ID reference of Elements Buffer Object
    GLuint ID{};

    // Constructor that generates a Elements Buffer Object and links it to indices
    explicit EBO(std::vector<GLuint> &indices);

    // Binds the EBO
    void Bind() const;

    // Unbinds the EBO
    static void Unbind();

    // Deletes the EBO
    void Delete();
};


#endif //OPENGLGAMECPP_EBO_H
