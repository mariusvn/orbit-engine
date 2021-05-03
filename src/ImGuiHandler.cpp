/*
 * Project: Orbit Engine
 * File: ImGui.cpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#include <Orbit/ImGuiHandler.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Orbit/Runtime.hpp>
#include <iostream>
#include <Orbit/SceneManager.hpp>

namespace Orbit {

    void ImGuiHandler::init(GLFWwindow *iwindow) {
        IMGUI_CHECKVERSION();
        ImGuiHandler::window = iwindow;
        ImGui::CreateContext();
        ImGuiIO &iodata = ImGui::GetIO();
        iodata.Fonts->AddFontFromFileTTF("assets\\fonts\\Segoe UI.ttf", 21);
        ImGuiHandler::io = &iodata;
        ImGui::StyleColorsDark();
        ImGuiHandler::setupImGuiStyle();
        ImGui_ImplGlfw_InitForOpenGL(iwindow, true);
        ImGui_ImplOpenGL3_Init();
    }

    void ImGuiHandler::startFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiHandler::render() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiHandler::destroy() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiHandler::startFrameBuffer() {
        glBindFramebuffer(GL_FRAMEBUFFER, ImGuiHandler::framebuffer);
        glBindTexture(GL_TEXTURE_2D, ImGuiHandler::texture);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindTexture(GL_TEXTURE_2D, 0);
        glViewport(0, 0, (int) ImGuiHandler::texResolution.x, (int) ImGuiHandler::texResolution.y);
    }

    void ImGuiHandler::stopFrameBuffer() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        int width, height;
        glfwGetFramebufferSize(ImGuiHandler::window, &width, &height);
        glViewport(0, 0, width, height);
    }

    void ImGuiHandler::initFrameBuffer(ImVec2 resolution) {
        ImGuiHandler::texResolution = resolution;
        glGenFramebuffers(1, &ImGuiHandler::framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, ImGuiHandler::framebuffer);

        glGenRenderbuffers(1, &ImGuiHandler::depthbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, ImGuiHandler::depthbuffer);

        glGenTextures(1, &ImGuiHandler::texture);
        glBindTexture(GL_TEXTURE_2D, ImGuiHandler::texture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (int) ImGuiHandler::texResolution.x,
                     (int) ImGuiHandler::texResolution.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, (int) ImGuiHandler::texResolution.x,
                              (int) ImGuiHandler::texResolution.y);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, ImGuiHandler::depthbuffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, ImGuiHandler::texture, 0);

        glBindTexture(GL_TEXTURE_2D, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void ImGuiHandler::deleteFrameBuffer() {
        glDeleteFramebuffers(1, &ImGuiHandler::framebuffer);
        glDeleteTextures(1, &ImGuiHandler::texture);
    }

    void ImGuiHandler::renderDebugMenu(unsigned int renderTexture, Orbit::Window *iwindow) {
        ImGui::SetNextWindowSize(ImVec2(iwindow->getWidth(), iwindow->getHeight()));
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowBgAlpha(1.0);
        ImGui::Begin("Orbit Engine##Main", nullptr,
                     ImGuiWindowFlags_NoCollapse |
                     ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoNav |
                     ImGuiWindowFlags_NoMove);
        void **tex = (void **) &renderTexture;
        int height = ImGui::GetContentRegionAvail().y;
        ImGui::BeginChild("Viewport", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.6f, height));
        {
            ImVec2 renderSize = ImVec2(ImGui::GetWindowContentRegionWidth(), height);
            const vec2 &vec = Runtime::getRenderResolution();
            if (vec.x != renderSize.x || vec.y != renderSize.y) {
                const vec2 nRenderRes = vec2(renderSize.x, renderSize.y);
                Runtime::setRenderResolution(nRenderRes);
            }
            ImGui::Image((void *) *tex,
                         renderSize,
                         ImVec2(0, 1),
                         ImVec2(1, 0));
        }
        ImGui::EndChild();
        ImGui::SameLine();
        ImGui::BeginChild("Inspector");
        const Scene *currentScene = SceneManager::getCurrentScene();
        ImGuiHandler::menu.drawInspector(currentScene);
        ImGui::EndChild();
        ImGui::End();
    }

    void ImGuiHandler::setViewportResolution(ImVec2 res) {
        ImGuiHandler::texResolution = res;
        glBindTexture(GL_TEXTURE_2D, ImGuiHandler::texture);
        glBindRenderbuffer(GL_RENDERBUFFER, ImGuiHandler::depthbuffer);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (int) res.x, (int) res.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, (int) res.x, (int) res.y);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void ImGuiHandler::setupImGuiStyle() {
        ImGuiStyle& style = ImGui::GetStyle();
        style.Colors[ImGuiCol_Text]                  = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        style.Colors[ImGuiCol_TextDisabled]          = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        style.Colors[ImGuiCol_WindowBg]              = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
        style.Colors[ImGuiCol_ChildBg]               = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
        style.Colors[ImGuiCol_PopupBg]               = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
        style.Colors[ImGuiCol_Border]                = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
        style.Colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style.Colors[ImGuiCol_FrameBg]               = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        style.Colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
        style.Colors[ImGuiCol_FrameBgActive]         = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
        style.Colors[ImGuiCol_TitleBg]               = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
        style.Colors[ImGuiCol_TitleBgActive]         = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
        style.Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
        style.Colors[ImGuiCol_MenuBarBg]             = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
        style.Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
        style.Colors[ImGuiCol_CheckMark]             = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
        style.Colors[ImGuiCol_SliderGrab]            = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
        style.Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.08f, 0.50f, 0.72f, 1.00f);
        style.Colors[ImGuiCol_Button]                = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        style.Colors[ImGuiCol_ButtonHovered]         = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
        style.Colors[ImGuiCol_ButtonActive]          = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
        style.Colors[ImGuiCol_Header]                = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
        style.Colors[ImGuiCol_HeaderHovered]         = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        style.Colors[ImGuiCol_HeaderActive]          = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
        style.Colors[ImGuiCol_Separator]             = style.Colors[ImGuiCol_Border];
        style.Colors[ImGuiCol_SeparatorHovered]      = ImVec4(0.41f, 0.42f, 0.44f, 1.00f);
        style.Colors[ImGuiCol_SeparatorActive]       = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style.Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.29f, 0.30f, 0.31f, 0.67f);
        style.Colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        style.Colors[ImGuiCol_Tab]                   = ImVec4(0.08f, 0.08f, 0.09f, 0.83f);
        style.Colors[ImGuiCol_TabHovered]            = ImVec4(0.33f, 0.34f, 0.36f, 0.83f);
        style.Colors[ImGuiCol_TabActive]             = ImVec4(0.23f, 0.23f, 0.24f, 1.00f);
        style.Colors[ImGuiCol_TabUnfocused]          = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
        style.Colors[ImGuiCol_TabUnfocusedActive]    = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
        style.Colors[ImGuiCol_PlotLines]             = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        style.Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
        style.Colors[ImGuiCol_DragDropTarget]        = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
        style.Colors[ImGuiCol_NavHighlight]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        style.Colors[ImGuiCol_NavWindowingDimBg]     = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        style.Colors[ImGuiCol_ModalWindowDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
        style.GrabRounding                           = style.FrameRounding = 2.3f;
        style.ItemSpacing                            = ImVec2(2, 2);
        style.WindowPadding                          = ImVec2(0, 0);
    }
}
