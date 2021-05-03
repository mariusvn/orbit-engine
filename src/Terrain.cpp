/*
 * Project: Orbit Engine
 * File: Terrain.cpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#include <Orbit/Terrain.hpp>
#include <iostream>
#include <Orbit/Logger.hpp>

namespace Orbit {

    void Terrain::loadModel(const char *path) {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture *> textures;
        Vertex vertex{};
        precision.x += 2;
        precision.y += 2;
        vec2 distBtwnPts = vec2(size.x / (float) precision.x, size.y / (float) precision.y);

        vertex.normal.x = 0;
        vertex.normal.y = 1;
        vertex.normal.z = 0;
        for (unsigned short y = 0; y < precision.y; y++) {
            for (unsigned short x = 0; x < precision.x; x++) {
                vertex.position.x = (float) x * distBtwnPts.x;
                vertex.position.z = (float) y * distBtwnPts.y;
                vertex.texCoords.x = ((float) x) / (float)precision.x;
                vertex.texCoords.y = ((float) y)  / (float)precision.y;
                vertices.push_back(vertex);
            }
        }

        for (unsigned short y = 1; y < precision.y; y++) {
            for (unsigned short x = 0; x < precision.x - 1; x++) {
                indices.push_back(getCoord(ivec2(x, y), precision));
                indices.push_back(getCoord(ivec2(x, y - 1), precision));
                indices.push_back(getCoord(ivec2(x + 1, y - 1), precision));
                indices.push_back(getCoord(ivec2(x, y), precision));
                indices.push_back(getCoord(ivec2(x + 1, y), precision));
                indices.push_back(getCoord(ivec2(x + 1, y - 1), precision));
            }
        }
        textures.push_back(new Texture("demo/assets/steve/steve.png"));
        meshes.emplace_back(vertices, indices, textures);
    }

    Terrain::Terrain(vec<2, unsigned short> precision, vec<2, float> size)
    : Model(nullptr), precision(precision), size(size) {
        this->loadModel(nullptr);
    }

    int Terrain::getCoord(ivec2 pos, ivec2 sizec) const {
        if (pos.x >= sizec.x) return 0;
        if (pos.x < 0) return 0;
        if (pos.y >= sizec.y) return 0;
        if (pos.y < 0) return 0;
        return (size.x  + 2) * pos.y + pos.x;
    }
}