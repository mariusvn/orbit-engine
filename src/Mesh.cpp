/*
 * Project: Orbit Engine
 * File: Mesh.cpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#include <Orbit/Mesh.hpp>
#include <glad/glad.h>
#include <utility>
#include <string>
#include <cstddef>

Orbit::Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture *> textures) {
    this->VAO = 0;
    this->VBO = 0;
    this->EBO = 0;
    this->vertices = std::move(vertices);
    this->indices = std::move(indices);
    this->textures = std::move(textures);
    setupMesh();
}

void Orbit::Mesh::draw(Orbit::Shader *shader) {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string uniformName;
        Texture::Type type = textures[i]->type;
        switch (type) {
            case Texture::TEX_DIFFUSE:
                uniformName = "texture_diffuse" + std::to_string(diffuseNr++);
                break;
            case Texture::TEX_SPECULAR:
                uniformName = "texture_specular" + std::to_string(specularNr++);
                break;
            case Texture::TEX_NORMAL:
                uniformName = "texture_normal" + std::to_string(normalNr++);
                break;
            case Texture::TEX_HEIGHT:
                uniformName = "texture_height" + std::to_string(heightNr++);
                break;
            default:
                continue;
        }

        glUniform1i(glGetUniformLocation(shader->getShaderProgram(), uniformName.c_str()), i);
        glBindTexture(GL_TEXTURE_2D, textures[i]->getTextureId());
    }


    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (GLsizei) indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);


    glActiveTexture(GL_TEXTURE0);
}

void Orbit::Mesh::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(vertices.size() * sizeof(Vertex)), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(indices.size() * sizeof(unsigned int)), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) nullptr);

    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, texCoords));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, bitangent));

    glBindVertexArray(0);
}
