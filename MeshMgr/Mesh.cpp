//
// Created by lucai on 10/18/2022.
//

#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, std::vector<Texture> &textures) {
    Mesh::vertices = vertices;
    Mesh::indices = indices;
    Mesh::textures = textures;

    // Generates Vertex Array Object and binds it
    VAO.Bind();
    // Generates Vertex Buffer Object and links it to vertices
    VBO VBO(vertices);
    // Generates Element Buffer Object and links it to indices
    EBO EBO(indices);

    // Links VBO attributes such as coordinates and colors to VAO
    // position
    VAO::LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void *) nullptr);
    // normals
    VAO::LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void *) (3 * sizeof(float)));
    // colours
    VAO::LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void *) (6 * sizeof(float)));
    // tex coords
    VAO::LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void *) (9 * sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    VAO.Unbind(); // NOLINT(readability-static-accessed-through-instance)
    VBO.Unbind(); // NOLINT(readability-static-accessed-through-instance)
    EBO.Unbind(); // NOLINT(readability-static-accessed-through-instance)
}

void Mesh::Draw(Shader &shader, Camera &camera) {
    shader.Activate();
    VAO.Bind();

    unsigned int numDiffuse = 0;
    unsigned int numSpecular = 0;

    for (GLint i = 0; i < textures.size(); i++) {
        std::string num;
        std::string type = textures[i].type;
        if (type == "diffuse") {
            num = std::to_string(numDiffuse++);
        } else if (type == "diffuse") {
            num = std::to_string(numSpecular++);
        }
        textures[i].texUnit(shader, (type + num).c_str(), i);
        textures[i].Bind();
    }
    glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
    camera.Matrix(shader, "camMatrix");

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT,
                   nullptr); // NOLINT(cppcoreguidelines-narrowing-conversions)
}
