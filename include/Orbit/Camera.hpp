/*
 * Project: Orbit Engine
 * File: Camera.hpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#ifndef ORBITENGINE_CAMERA_HPP
#define ORBITENGINE_CAMERA_HPP

#include <Orbit/Types.hpp>
#include <Orbit/Transformable.hpp>

namespace Orbit {
    struct Camera : public Transformable {
    public:
        mat4 getTransformMatrix() const override;
        unsigned char getFOV() const;
        void setFOV(unsigned char val);
    private:
        unsigned char fov;
    };
}

#endif //ORBITENGINE_CAMERA_HPP
