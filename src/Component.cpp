/*
 * Project: Orbit Engine
 * File: Component.cpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#include <Orbit/Component.hpp>
#include <Orbit/GameObject.hpp>

namespace Orbit {

    GameObject &Component::getGameObject() const {
        return *(this->gameObject);
    }

    const std::string &Component::getComponentName() const {
        return this->name;
    }

    void Component::assignGameObject(GameObject* gm) {
        // TODO(marius): Add verifications
        this->gameObject = gm;
        gm->components.push_back(this);
    }

    bool Component::isEnabled() const {
        return this->isComponentEnabled;
    }

    void Component::enable() {
        if (this->isComponentEnabled) return;
        this->isComponentEnabled = true;
        this->onEnable();
    }

    void Component::disable() {
        if (!this->isComponentEnabled) return;
        this->isComponentEnabled = false;
        this->onDisable();
    }
}