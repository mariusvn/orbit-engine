/*
 * Project: Orbit Engine
 * File: Input.hpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#ifndef ORBITENGINE_INPUT_HPP
#define ORBITENGINE_INPUT_HPP

#include <Orbit/Keys.hpp>
#include <Orbit/Window.hpp>
#include <Orbit/Types.hpp>

namespace Orbit {
    class Input {
    public:
        static void initInput(Window* window);
        static bool isKeyPressed(int key);
        static dvec2 getMousePosition();
        static void setMouseVisible(bool visible);
        // NOTE(marius): only if cursor disabled
        static void setRawMouseMotion(bool active);
    private:
        explicit Input() = default;
        inline static GLFWwindow *window = nullptr;
    };
}

#endif //ORBITENGINE_INPUT_HPP
