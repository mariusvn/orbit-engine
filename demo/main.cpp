/*
 * Project: Orbit Engine
 * File: main.cpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#include <Orbit/Window.hpp>
#include <Orbit/Runtime.hpp>
#include <Orbit/SceneManager.hpp>
#include <stdexcept>


int main() {
    Orbit::Window* window = new Orbit::Window(1280, 720, "Orbit Engine");
    try {
        Orbit::Model *testModel = new Orbit::Model("demo/assets/steve/steve.obj");
        Orbit::Scene *scene = new Orbit::Scene();
        Orbit::GameObject *gameObject = new Orbit::GameObject();
        Orbit::GameObject *gameObjectb = new Orbit::GameObject();

        gameObject->model = testModel;
        gameObjectb->name = "Test Object";
        gameObject->children.push_back(gameObjectb);

        scene->camera.translate(Orbit::vec3(0, -5.0f, -10.0f));

        gameObject->rotate(Orbit::vec3(0, -90, 0));
        scene->root = gameObject;

        Orbit::SceneManager::setCurrentScene(scene);
        Orbit::Runtime::execute(window);
        delete window;
    } catch (std::exception &e) {
        window->close();
        delete window;
        throw std::runtime_error(e.what());
    }
    return 0;
}