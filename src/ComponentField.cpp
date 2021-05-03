/*
 * Project: Orbit Engine
 * File: ComponentField.cpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#include <Orbit/ComponentField.hpp>
#include <Orbit/ImGuiHandler.hpp>
#include <cstring>

namespace Orbit {

    const char *ComponentField::getName() const {
        return this->name;
    }

    void ComponentField::drawImGuiInspector() {
        switch (this->type) {
            case String:
                ComponentField::drawInspector(this->name, (const char **) this->ptr);
                break;
            case Int:
                ComponentField::drawInspector(this->name, (int *) this->ptr);
                break;
            case Float:
                ComponentField::drawInspector(this->name, (float *) this->ptr);
                break;
        }
    }

    void ComponentField::drawInspector(const char *name, const char **data) {
        assert(data);
        assert(*data);
        unsigned int len = strlen(*data);
        char buf[len + 1];
        strcpy(buf, *data);
        buf[len] = '\0';
        ImGui::InputText(name, buf, len + 1);
        if (strcmp(buf, *data) != 0)
            *data = buf;
    }

    void ComponentField::drawInspector(const char *name, int *data) {
        assert(data);
        ImGui::InputInt(name, data);
    }

    void ComponentField::drawInspector(const char *name, float *data) {
        assert(data);
        ImGui::DragFloat(name, data, 0.2f);
    }


}