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

namespace Orbit {

    void ImGuiHandler::init(GLFWwindow* window) {
        IMGUI_CHECKVERSION();
        ImGuiHandler::window = window;
        ImGui::CreateContext();
        ImGuiIO& iodata = ImGui::GetIO();
        ImGuiHandler::io = &iodata;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
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
        glViewport(0,0,(int)ImGuiHandler::texResolution.x,(int)ImGuiHandler::texResolution.y);
    }

    void ImGuiHandler::stopFrameBuffer() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        int width, height;
        glfwGetFramebufferSize(ImGuiHandler::window, &width, &height);
        glViewport(0,0,width,height);
    }

    void ImGuiHandler::initFrameBuffer(ImVec2 resolution) {
        ImGuiHandler::texResolution = resolution;
        glGenFramebuffers(1, &ImGuiHandler::framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, ImGuiHandler::framebuffer);

        glGenRenderbuffers(1, &ImGuiHandler::depthbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, ImGuiHandler::depthbuffer);

        glGenTextures(1, &ImGuiHandler::texture);
        glBindTexture(GL_TEXTURE_2D, ImGuiHandler::texture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (int)ImGuiHandler::texResolution.x, (int)ImGuiHandler::texResolution.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, (int)ImGuiHandler::texResolution.x, (int)ImGuiHandler::texResolution.y);
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

    void ImGuiHandler::renderDebugMenu(unsigned int renderTexture, Orbit::Window* window) {
        ImGui::SetNextWindowSize(ImVec2(window->getWidth(), window->getHeight()));
        ImGui::SetNextWindowPos(ImVec2(0,0));
        ImGui::SetNextWindowBgAlpha(1.0);
        ImGui::Begin("Orbit Engine##Main", nullptr,
                     ImGuiWindowFlags_NoCollapse |
                     ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoNav |
                     ImGuiWindowFlags_NoMove);
        void **tex = (void**) &renderTexture;
        ImGui::BeginChild("Viewport", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.6f, window->getHeight() - 35));
        {
            ImVec2 renderSize = ImVec2(ImGui::GetWindowContentRegionWidth(), window->getHeight() - 35);
            const vec2& vec = Runtime::getRenderResolution();
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
        static ImGuiTableFlags flags = ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody;
        if (ImGui::BeginTable("inspectorTable", 2, flags, ImVec2(ImGui::GetWindowContentRegionWidth(), window->getHeight() - 35))) {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Inspector tree");
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("Inspector item");
            ImGui::EndTable();
        }
        ImGui::EndChild();
        ImGui::End();
    }

    void ImGuiHandler::setViewportResolution(ImVec2 res) {
        ImGuiHandler::texResolution = res;
        glBindTexture(GL_TEXTURE_2D, ImGuiHandler::texture);
        glBindRenderbuffer(GL_RENDERBUFFER, ImGuiHandler::depthbuffer);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (int)res.x, (int)res.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, (int)res.x, (int)res.y);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
