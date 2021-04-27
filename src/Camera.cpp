/*
 * Project: Orbit Engine
 * File: Camera.cpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#include <Orbit/Camera.hpp>

Orbit::mat4 Orbit::Camera::getTransformMatrix() const {
    return Transformable::getTransformMatrix();
}

unsigned char Orbit::Camera::getFOV() const {
    return this->fov;
}

void Orbit::Camera::setFOV(unsigned char val) {
    this->fov = val;
}
