/*
 * Project: Orbit Engine
 * File: Transformable.cpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#include <Orbit/Transformable.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace Orbit {

    vec3 Transformable::getPosition() const {
        return this->position;
    }

    vec3 Transformable::getRotation() const {
        return this->rotation;
    }

    vec3 Transformable::getScale() const {
        return this->scale;
    }

    void Transformable::setPosition(vec3 pos) {
        this->position = pos;
    }

    void Transformable::setRotation(vec3 rot) {
        this->rotation = rot;
    }

    void Transformable::setScale(vec3 sc) {
        this->scale = sc;
    }

    void Transformable::translate(vec3 vec) {
        this->position += vec;
    }

    void Transformable::rotate(vec3 vec) {
        this->rotation += vec;
    }

    void Transformable::resize(vec3 vec) {
        this->scale *= vec;
    }

    mat4 Transformable::getTransformMatrix() const {
        mat4 transform = mat4(1.0f);
        transform = glm::rotate(transform, glm::radians(this->rotation.x), vec3(1, 0, 0));
        transform = glm::rotate(transform, glm::radians(this->rotation.y), vec3(0, 1, 0));
        transform = glm::rotate(transform, glm::radians(this->rotation.z), vec3(0, 0, 1));
        transform = glm::translate(transform, this->position);
        transform = glm::scale(transform, this->scale);
        return transform;
    }
}