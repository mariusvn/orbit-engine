/*
 * Project: Orbit Engine
 * File: Input.cpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#include <Orbit/Input.hpp>
#include <Orbit/Types.hpp>

namespace Orbit {

    void Input::initInput(Window *win) {
        Input::window = &win->getInstance();
    }

    bool Input::isKeyPressed(int key) {
        int state = glfwGetKey(Input::window, key);
        int mouseState = glfwGetMouseButton(Input::window, key);
        return (state == GLFW_PRESS || mouseState == GLFW_PRESS);
    }

    dvec2 Input::getMousePosition() {
        double x, y;
        glfwGetCursorPos(Input::window, &x, &y);
        return vec<2, double>(x, y);
    }

    void Input::setMouseVisible(bool visible) {
        const int flag = visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED;
        glfwSetInputMode(Input::window, GLFW_CURSOR, flag);
    }

    void Input::setRawMouseMotion(bool active) {
        const int t = active ? GLFW_TRUE : GLFW_FALSE;
        if (glfwRawMouseMotionSupported())
            glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }

}