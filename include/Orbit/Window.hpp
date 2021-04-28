/*
 * Project: Orbit Engine
 * File: Window.hpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#ifndef ORBITENGINE_WINDOW_HPP
#define ORBITENGINE_WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Orbit {

    class Window {
    public:
        explicit Window(unsigned short width, unsigned short height, const char *name);
        ~Window();
        bool isOpen() const;
        void close();
        void pollEvent();
        void display();
        bool isFocused() const;
        unsigned short getWidth() const;
        unsigned short getHeight() const;

    private:
        GLFWwindow *window = nullptr;
        bool shouldClose = false;
        unsigned short width;
        unsigned short height;
    };

}

#endif //ORBITENGINE_WINDOW_HPP
