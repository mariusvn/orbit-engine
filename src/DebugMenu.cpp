/*
 * Project: Orbit Engine
 * File: DebugMenu.cpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#include <Orbit/DebugMenu.hpp>
#include <Orbit/Runtime.hpp>
#include <ImGUI/imgui.h>
#include <limits>
#include <Orbit/Logger.hpp>

void Orbit::DebugMenu::drawInspector(const Orbit::Scene *scene) {
    static ImGuiTableFlags flags =
            ImGuiTableFlags_SizingStretchSame |
            ImGuiTableFlags_Resizable |
            ImGuiTableFlags_BordersOuter |
            ImGuiTableFlags_BordersV |
            ImGuiTableFlags_RowBg;
    if (ImGui::BeginTable("inspectorTable", 2, flags,
                          ImVec2(ImGui::GetWindowContentRegionWidth(), Runtime::getRenderResolution().y))) {

        ImGui::TableSetupColumn("Game Objects Hierarchy", ImGuiTableColumnFlags_NoHide);
        ImGui::TableSetupColumn("Game Object Inspector");
        ImGui::TableHeadersRow();

        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        this->drawGameObjectHierarchy(scene);
        ImGui::TableSetColumnIndex(1);
        if (this->targetGameObject) {
            ImGui::Text("%s", this->targetGameObject->name.c_str());
            this->drawTagetProperties();
        } else {
            ImGui::Text("No Game Object Selected");
        }

        ImGui::EndTable();
    }
}

void Orbit::DebugMenu::drawGameObjectHierarchy(const Orbit::Scene *scene) {
    if (scene) {
        drawGameObjectItem(scene->root, 1);

    } else {
        ImGui::Text("No scene loaded");
    }
}

void Orbit::DebugMenu::drawGameObjectItem(Orbit::GameObject *go, unsigned long long int index) {
    ImGuiTreeNodeFlags flags =
            ImGuiTreeNodeFlags_OpenOnArrow |
            ImGuiTreeNodeFlags_OpenOnDoubleClick |
            ImGuiTreeNodeFlags_SpanAvailWidth;
    if (go == this->targetGameObject)
        flags |= ImGuiTreeNodeFlags_Selected;
    if (go->children.empty())
        flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
    std::string label = (go->name + "##" + std::to_string(index));
    bool nodeOpen = ImGui::TreeNodeEx(label.c_str(), flags);
    if (ImGui::IsItemClicked()) {
        this->targetGameObject = go;
    }
    if (nodeOpen && !go->children.empty()) {
        for (unsigned long long i = 0; i < go->children.size(); i++)
            if (go->children[i] != nullptr)
                this->drawGameObjectItem(go->children[i], index + i * SHRT_MAX);
        ImGui::TreePop();
    }
}

void Orbit::DebugMenu::drawTagetProperties() {
    GameObject *target = this->targetGameObject;

    ImGui::BeginChild("targetProperties", ImVec2(ImGui::GetContentRegionAvailWidth(), -10));
    ImGui::Text("Transform");
    {
        // NOTE(marius): Position
        vec3 targetPosition = target->getPosition();
        float pos[3] = {targetPosition.x, targetPosition.y, targetPosition.z};
        ImGui::DragFloat3("Position", pos);
        if (targetPosition.x != pos[0] || targetPosition.y != pos[1] || targetPosition.z != pos[2])
            target->setPosition(vec3(pos[0], pos[1], pos[2]));
    }
    {
        // NOTE(marius): Rotation
        vec3 targetRotation = target->getRotation();
        float rot[3] = {targetRotation.x, targetRotation.y, targetRotation.z};
        ImGui::DragFloat3("Rotation", rot);
        if (targetRotation.x != rot[0] || targetRotation.y != rot[1] || targetRotation.z != rot[2])
            target->setRotation(vec3(rot[0], rot[1], rot[2]));
    }
    {
        // NOTE(marius): Scale
        vec3 targetScale = target->getScale();
        float scale[3] = {targetScale.x, targetScale.y, targetScale.z};
        ImGui::DragFloat3("Scale", scale);
        if (targetScale.x != scale[0] || targetScale.y != scale[1] || targetScale.z != scale[2])
            target->setScale(vec3(scale[0], scale[1], scale[2]));
    }
    {
        for (unsigned short i  = 0; i < target->components.size(); i++) {
            Component *component = target->components[i];
            ImGui::Separator();

            if (ImGui::CollapsingHeader(component->name.c_str())) {

                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding,  ImVec2(5.0f, 5.0f));
                ImGui::BeginChild(("CompField" + std::to_string(i)).c_str(), ImVec2(0, 0), false, ImGuiWindowFlags_AlwaysUseWindowPadding);

                bool checked = component->isEnabled();
                ImGui::Checkbox("Active", &checked);

                if (checked != component->isEnabled()) {
                    if (checked) component->enable();
                    else component->disable();
                }

                for (ComponentField *field : component->fields)
                    field->drawImGuiInspector();
                ImGui::EndChild();
                ImGui::PopStyleVar();
            }
        }
    }
    ImGui::EndChild();
}
