/*
 * Project: Orbit Engine
 * File: DebugMenu.hpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#ifndef ORBITENGINE_DEBUGMENU_HPP
#define ORBITENGINE_DEBUGMENU_HPP

#include <Orbit/Scene.hpp>

namespace Orbit {
    class DebugMenu {
    public:
        explicit DebugMenu() = default;
        ~DebugMenu() = default;

        void drawInspector(const Scene* scene);

    private:
        void drawGameObjectHierarchy(const Scene* scene);
        void drawGameObjectItem(GameObject* go, unsigned long long int index);
        void drawTagetProperties();

        GameObject* targetGameObject = nullptr;
    };
}

#endif //ORBITENGINE_DEBUGMENU_HPP
