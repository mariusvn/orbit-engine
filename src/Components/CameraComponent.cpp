/*
 * Project: Orbit Engine
 * File: CameraComponent.cpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#include <Orbit/Components/CameraComponent.hpp>
#include <Orbit/SceneManager.hpp>
#include <Orbit/Input.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <iostream>

namespace Orbit {

    CameraComponent::CameraComponent(): Orbit::Component("Camera Movements") {

    }

    void CameraComponent::onInit() {
        this->camera = &(SceneManager::getCurrentScene()->camera);
        this->fields.push_back(new Orbit::ComponentField(Orbit::ComponentField::Float, "Speed", &this->translate_speed));
        this->fields.push_back(new Orbit::ComponentField(Orbit::ComponentField::Float, "Sensibility", &this->rotation_speed));
        this->fields.push_back(new Orbit::ComponentField(Orbit::ComponentField::Float, "Run Multiplier", &this->run_multiplier));
    }

    void CameraComponent::onUpdate() {
        if (Input::isKeyPressed(ORBIT_MOUSE_BUTTON_RIGHT) && !this->last_right_click) {
            this->mouse_attached = !this->mouse_attached;
            Input::setMouseVisible(!this->mouse_attached);
            Input::setRawMouseMotion(this->mouse_attached);
            if (!this->mouse_attached) {
                this->lastMousePos.x = -1;
                this->lastMousePos.y = -1;
            }
        }
        this->last_right_click = Input::isKeyPressed(ORBIT_MOUSE_BUTTON_RIGHT);

        float transFactor = this->translate_speed / 2;
        if (Input::isKeyPressed(ORBIT_KEY_LEFT_SHIFT) || Input::isKeyPressed(ORBIT_KEY_RIGHT_SHIFT))
            transFactor *= 4 * run_multiplier;

        if (this->mouse_attached) {
            if (this->lastMousePos.x == -1) {
                this->lastMousePos = Input::getMousePosition();
            } else {
                auto mpos = Input::getMousePosition();
                auto diff = mpos - lastMousePos;
                this->camera->rotate(vec3((diff.y * this->rotation_speed) / 3, (diff.x * this->rotation_speed) / 3, 0));
                this->lastMousePos = mpos;
                if (this->camera->getRotation().x > 85) {
                    vec3 rot = this->camera->getRotation();
                    rot.x = 85;
                    this->camera->setRotation(rot);
                } else if (this->camera->getRotation().x < -85) {
                    vec3 rot = this->camera->getRotation();
                    rot.x = -85;
                    this->camera->setRotation(rot);
                }
            }
        }
        if (Input::isKeyPressed(ORBIT_KEY_W)) {
            this->move(vec3(0,0, transFactor));
        }
        if (Input::isKeyPressed(ORBIT_KEY_S)) {
            this->move(vec3(0,0,-1 * transFactor));
        }
        if (Input::isKeyPressed(ORBIT_KEY_D)) {
            this->move(vec3(-1 * transFactor, 0, 0), true);
        }
        if (Input::isKeyPressed(ORBIT_KEY_A)) {
            this->move(vec3(transFactor, 0, 0), true);
        }
        if (Input::isKeyPressed(ORBIT_KEY_Q)) {
            this->camera->translate(vec3(0, transFactor, 0));
        }
        if (Input::isKeyPressed(ORBIT_KEY_E)) {
            this->camera->translate(vec3(0, -1 * transFactor, 0));
        }
    }

    void CameraComponent::onEnable() {
        this->camera = &(SceneManager::getCurrentScene()->camera);
    }

    void CameraComponent::onDisable() {

    }

    void CameraComponent::onUnload() {

    }

    void CameraComponent::move(vec3 trans, bool ignoreX) {
        vec3 rot = this->camera->getRotation();
        if (ignoreX)
            rot.x = 0;
        glm::mat4 transform = glm::eulerAngleXYZ(
                glm::radians(-1 * rot.x),
                glm::radians(-1 * rot.y),
                glm::radians(-1 * rot.z));
        transform = glm::translate(transform, trans);
        this->camera->translate(vec3(transform[3]));
    }
}