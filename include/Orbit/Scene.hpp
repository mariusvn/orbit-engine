/*
 * Project: Orbit Engine
 * File: Scene.hpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#ifndef ORBITENGINE_SCENE_HPP
#define ORBITENGINE_SCENE_HPP

#include <Orbit/GameObject.hpp>
#include <Orbit/Camera.hpp>

namespace Orbit {
    class Scene {
    public:
        GameObject *root = nullptr;
        Camera camera;
    };
}

#endif //ORBITENGINE_SCENE_HPP
