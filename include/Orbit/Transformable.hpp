/*
 * Project: Orbit Engine
 * File: Transformable.hpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#ifndef ORBITENGINE_TRANSFORMABLE_HPP
#define ORBITENGINE_TRANSFORMABLE_HPP

#include <glm/glm.hpp>
#include <Orbit/Types.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Orbit {
    class Transformable {
    public:
        vec3 getPosition() const;
        vec3 getRotation() const;
        vec3 getScale() const;
        void setPosition(vec3 position);
        void setRotation(vec3 rotation);
        void setScale(vec3 scale);
        void translate(vec3 vec);
        void rotate(vec3 vec);
        void resize(vec3 vec);

    protected:
        virtual mat4 getTransformMatrix() const;
        bool turnAround = true;

    private:
        vec3 position{};
        vec3 rotation{};
        vec3 scale = {1.0f, 1.0f, 1.0f};
    };
}

#endif //ORBITENGINE_TRANSFORMABLE_HPP
