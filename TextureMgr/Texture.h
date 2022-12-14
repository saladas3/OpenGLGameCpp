//
// Created by lucai on 10/16/2022.
//

#ifndef OPENGLGAMECPP_TEXTURE_H
#define OPENGLGAMECPP_TEXTURE_H

#include <glad/glad.h>
#include "../stb/stb_image.h"
#include "../ShaderMgr/Shader.h"

class Texture {
public:
    GLuint ID{};
    GLuint unit;
    const char *type;

    Texture(const char* image, const char* texType, GLuint slot);

    // Assigns a texture unit to a texture
    static void texUnit(Shader &shader, const char *uniform, GLint unit);

    // Binds a texture
    void Bind() const;

    // Unbinds a texture
    static void Unbind() ;

    // Deletes a texture
    void Delete();
};


#endif //OPENGLGAMECPP_TEXTURE_H
