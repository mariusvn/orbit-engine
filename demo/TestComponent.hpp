/*
 * Project: Orbit Engine
 * File: TestComponent.hpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */


#ifndef ORBITENGINE_TESTCOMPONENT_HPP
#define ORBITENGINE_TESTCOMPONENT_HPP

#include <Orbit/Component.hpp>

class TestComponent: public Orbit::Component {
public:
    explicit TestComponent(const std::string& name);

    void onInit() final;
    void onUpdate() final;
    void onEnable() final;
    void onDisable() final;
    void onUnload() final;

private:
    float speed = 0.0f;
};


#endif
