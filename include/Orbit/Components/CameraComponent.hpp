/*
 * Project: Orbit Engine
 * File: CameraComponent.hpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#ifndef ORBITENGINE_CAMERACOMPONENT_HPP
#define ORBITENGINE_CAMERACOMPONENT_HPP

#include <Orbit/Component.hpp>
#include <Orbit/Camera.hpp>
#include <Orbit/Types.hpp>

namespace Orbit {
    class CameraComponent: public Orbit::Component {
    public:
        explicit CameraComponent();

        void onInit() final;
        void onUpdate() final;
        void onEnable() final;
        void onDisable() final;
        void onUnload() final;

    private:
        Orbit::Camera* camera = nullptr;
        float translate_speed = 1.0f;
        float rotation_speed = 1.0f;
        float run_multiplier = 1.0f;
        bool mouse_attached = false;
        bool last_right_click = false;
        dvec2 lastMousePos = dvec2(-1, -1);

        void move(vec3 trans, bool ignoreX = false);
    };
}

#endif //ORBITENGINE_CAMERACOMPONENT_HPP
