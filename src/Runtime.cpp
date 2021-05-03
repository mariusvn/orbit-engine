/*
 * Project: Orbit Engine
 * File: Runtime.cpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#include <Orbit/Runtime.hpp>
#include <Orbit/SceneManager.hpp>
#include <cassert>
#include <Orbit/ImGuiHandler.hpp>

namespace Orbit {

    void Runtime::execute(Window *window) {
        assert(window);
        Runtime::setRenderResolution(vec2(window->getWidth(), window->getHeight()));
        ImGuiHandler::initFrameBuffer(ImVec2(window->getWidth(), window->getHeight()));
        Runtime::initCurrentScene();
        while (window->isOpen()) {
            window->pollEvent();
            if (ImGuiHandler::isDebugMenu) {
                ImGuiHandler::startFrame();
                ImGuiHandler::startFrameBuffer();
            }
            Runtime::render(window);
            if (ImGuiHandler::isDebugMenu) {
                ImGuiHandler::stopFrameBuffer();
                ImGuiHandler::renderDebugMenu(ImGuiHandler::texture, window);
                ImGuiHandler::render();
            }
            window->display();
            Runtime::updateCurrentScene();
        }
        Runtime::unloadCurrentScene();
        ImGuiHandler::deleteFrameBuffer();
        ImGuiHandler::destroy();
    }

    void Runtime::render(Window *window) {
        const Scene *currentScene = SceneManager::getCurrentScene();
        mat4 transform;

        if (!currentScene || !currentScene->root)
            return;

        transform = glm::perspective(
                glm::radians((float) currentScene->camera.getFOV()),
                (float) Runtime::renderResolution.x / (float) Runtime::renderResolution.y,
                0.1f,
                1000.0f);
        transform *= currentScene->camera.getTransformMatrix();
        currentScene->root->draw(transform);
    }

    void Runtime::setRenderResolution(vec2 res) {
        Runtime::renderResolution.x = res.x;
        Runtime::renderResolution.y = res.y;
        ImGuiHandler::setViewportResolution(ImVec2(res.x, res.y));
    }

    const vec2 &Runtime::getRenderResolution() {
        return Runtime::renderResolution;
    }

    void Runtime::updateCurrentScene() {
        const Scene *currentScene = SceneManager::getCurrentScene();
        if (currentScene->root)
            currentScene->root->update();
    }

    void Runtime::initCurrentScene() {
        const Scene *currentScene = SceneManager::getCurrentScene();
        if (currentScene->root)
            currentScene->root->init();
    }

    void Runtime::unloadCurrentScene() {
        const Scene *currentScene = SceneManager::getCurrentScene();
        if (currentScene->root)
            currentScene->root->unload();
    }
}