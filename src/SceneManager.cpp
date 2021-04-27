/*
 * Project: Orbit Engine
 * File: SceneManagercpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#include <Orbit/SceneManager.hpp>

namespace Orbit {

    void SceneManager::setCurrentScene(Scene *scene) {
        SceneManager::currentScene = scene;
    }

    const Scene *SceneManager::getCurrentScene() {
        return SceneManager::currentScene;
    }
}