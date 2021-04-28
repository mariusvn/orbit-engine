/*
 * Project: Orbit Engine
 * File: SceneManager.hpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#ifndef ORBITENGINE_SCENEMANAGER_HPP
#define ORBITENGINE_SCENEMANAGER_HPP

#include <Orbit/Scene.hpp>

namespace Orbit {
    class SceneManager {
    public:
        static void setCurrentScene(Scene *scene);
        static const Scene *getCurrentScene();

    private:
        explicit SceneManager() = default;

        inline static Scene *currentScene = nullptr;
    };
}

#endif //ORBITENGINE_SCENEMANAGER_HPP
