/*
 * Project: Orbit Engine
 * File: main.cpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#include <Orbit/Window.hpp>
#include <Orbit/Runtime.hpp>
#include <Orbit/SceneManager.hpp>
#include <stdexcept>
#include "TestComponent.hpp"
#include <Orbit/Components/CameraComponent.hpp>

int main() {
    Orbit::Window *window = new Orbit::Window(1600, 900, "Orbit Engine");
    try {
        Orbit::Model *testModel = new Orbit::Model("demo/assets/steve/steve.obj");
        Orbit::Scene *scene = new Orbit::Scene();
        Orbit::GameObject *gameObject = new Orbit::GameObject();
        Orbit::GameObject *gameObjectb = new Orbit::GameObject();
        TestComponent *testComponent = new TestComponent("testComponent");
        Orbit::CameraComponent *cameraComponent = new Orbit::CameraComponent();

        gameObject->model = testModel;
        testComponent->assignGameObject(gameObject);
        cameraComponent->assignGameObject(gameObject);
        gameObjectb->name = "Test Object";
        gameObject->children.push_back(gameObjectb);

        scene->camera.translate(Orbit::vec3(0, -5.0f, -10.0f));

        gameObject->rotate(Orbit::vec3(0, -90, 0));
        scene->root = gameObject;

        Orbit::SceneManager::setCurrentScene(scene);
        Orbit::Runtime::execute(window);
        delete window;
        delete testModel;
        delete scene;
        delete gameObject;
        delete gameObjectb;
    } catch (std::exception &e) {
        window->close();
        delete window;
        throw std::runtime_error(e.what());
    }
    return 0;
}