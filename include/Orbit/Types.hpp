/*
 * Project: Orbit Engine
 * File: Types.hpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#ifndef ORBITENGINE_TYPES_HPP
#define ORBITENGINE_TYPES_HPP

#include <glm/glm.hpp>

namespace Orbit {
    using vec2 = glm::vec2;
    using vec3 = glm::vec3;
    using vec4 = glm::vec4;
    template<int L, typename T>
    using vec = glm::vec<L, T, glm::defaultp>;
    using ivec2 = glm::ivec2;
    using ivec3 = glm::ivec3;
    using ivec4 = glm::ivec4;
    using mat4 = glm::mat4;
    using mat3 = glm::mat3;
    using mat2 = glm::mat2;
    using dvec1 = glm::dvec1;
    using dvec2 = glm::dvec2;
    using dvec3 = glm::dvec3;
    using dvec4 = glm::dvec4;
}

#endif //ORBITENGINE_TYPES_HPP
