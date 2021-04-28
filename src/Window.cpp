/*
 * Project: Orbit Engine
 * File: Window.cpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#include <Orbit/Window.hpp>
#include <stdexcept>
#include <Orbit/ImGuiHandler.hpp>

namespace Orbit {

    Window::Window(unsigned short width, unsigned short height, const char *name) {
        this->width = width;
        this->height = height;

        try {

            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

            this->window = glfwCreateWindow(width, height, name, nullptr, nullptr);

            if (this->window == nullptr) {
                glfwTerminate();
                throw std::runtime_error("Failed to create GLFW window.");
            }

            glfwMakeContextCurrent(this->window);

            if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
                throw std::runtime_error("Failed to initialize GLAD");
            }

            glfwSwapInterval(1);

            glViewport(0, 0, width, height);
            glClearColor(0.2, 0.2, 0.2, 0.5);
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);

            ImGuiHandler::init(this->window);
            this->pollEvent();
        } catch (std::exception &e) {
            this->close();
            delete this;
            throw std::runtime_error(e.what());
        }
    }

    Window::~Window() {
        glfwTerminate();
    }

    bool Window::isOpen() const {
        if (this->shouldClose) return true;
        return !glfwWindowShouldClose(this->window);
    }

    void Window::close() {
        this->shouldClose = true;
    }

    void Window::pollEvent() {
        glfwPollEvents();
    }

    void Window::display() {
        glfwSwapBuffers(this->window);
        if (!ImGuiHandler::isDebugMenu)
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    bool Window::isFocused() const {
        return (bool) glfwGetWindowAttrib(window, GLFW_FOCUSED);
    }

    unsigned short Window::getWidth() const {
        return this->width;
    }

    unsigned short Window::getHeight() const {
        return this->height;
    }

}