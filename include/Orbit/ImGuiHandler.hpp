/*
 * Project: Orbit Engine
 * File: ImGui.hpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#ifndef ORBITENGINE_IMGUIHANDLER_HPP
#define ORBITENGINE_IMGUIHANDLER_HPP

#include <ImGUI/imgui.h>
#include <ImGUI/imgui_impl_opengl3.h>
#include <ImGUI/imgui_impl_glfw.h>
#include <Orbit/Window.hpp>
#include <Orbit/DebugMenu.hpp>

namespace Orbit {

    class ImGuiHandler {
    public:
        static void init(GLFWwindow *iwindow);
        static void startFrameBuffer();
        static void stopFrameBuffer();
        static void initFrameBuffer(ImVec2 res);
        static void deleteFrameBuffer();
        static void startFrame();
        static void render();
        static void destroy();
        static void renderDebugMenu(unsigned int renderTexture, Orbit::Window *iwindow);
        static void setViewportResolution(ImVec2 res);


        inline static unsigned int framebuffer;
        inline static unsigned int texture;
        inline static unsigned int depthbuffer;
        inline static ImVec2 texResolution;
        inline static bool isDebugMenu = true;
    private:
        explicit ImGuiHandler() = default;

        static void setupImGuiStyle();

        inline static ImGuiIO *io = nullptr;
        inline static GLFWwindow *window = nullptr;
        inline static DebugMenu menu = DebugMenu();
    };

}

#endif //ORBITENGINE_IMGUIHANDLER_HPP
