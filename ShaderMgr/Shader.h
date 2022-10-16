//
// Created by lucai on 10/16/2022.
//

#ifndef OPENGLGAMECPP_SHADER_H
#define OPENGLGAMECPP_SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <cstring>

std::string getFileContents(const char *fileName);

class Shader {
public:
    GLuint ID{};
    Shader(const char *vertexFile, const char *fragmentFile);
    void Activate() const;
    void Delete() const;
private:
    // Checks if the different Shaders have compiled properly
    static void compileErrors(unsigned int shader, const char* type);
};


#endif //OPENGLGAMECPP_SHADER_H
