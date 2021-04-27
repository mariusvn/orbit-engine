/*
 * Project: Orbit Engine
 * File: Vertex.hpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#ifndef ORBITENGINE_VERTEX_HPP
#define ORBITENGINE_VERTEX_HPP

#include <Orbit/Types.hpp>

namespace Orbit {
    struct Vertex {
        vec3 position;
        vec3 normal;
        vec2 texCoords;
        vec3 tangent;
        vec3 bitangent;
    };
}

#endif //ORBITENGINE_VERTEX_HPP
