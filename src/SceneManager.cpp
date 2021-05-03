/*
 * Project: Orbit Engine
 * File: SceneManager.cpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#include <Orbit/SceneManager.hpp>

namespace Orbit {

    void SceneManager::setCurrentScene(Scene *scene) {
        SceneManager::currentScene = scene;
    }

    Scene *SceneManager::getCurrentScene() {
        return SceneManager::currentScene;
    }
}