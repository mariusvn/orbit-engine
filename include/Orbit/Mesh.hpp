/*
 * Project: Orbit Engine
 * File: Mesh.hpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#ifndef ORBITENGINE_MESH_HPP
#define ORBITENGINE_MESH_HPP

#include <Orbit/Vertex.hpp>
#include <Orbit/Texture.hpp>
#include <Orbit/Shader.hpp>
#include <vector>

namespace Orbit {
    class Mesh {
    public:
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture *> textures);
        void draw(Shader *shader);
        void updateTextures(Shader *shader);

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture *> textures;
        unsigned int VAO;

    private:
        void setupMesh();

        unsigned int VBO, EBO;
    };
}

#endif //ORBITENGINE_MESH_HPP
