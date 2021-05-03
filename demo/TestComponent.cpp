/*
 * Project: Orbit Engine
 * File: TestComponent.cpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */


#include "TestComponent.hpp"
#include <Orbit/GameObject.hpp>
#include <string>
#include <iostream>
#include <Orbit/Input.hpp>

TestComponent::TestComponent(const std::string& name): Orbit::Component(name.c_str()) {}

void TestComponent::onInit() {
    this->fields.push_back(new Orbit::ComponentField(Orbit::ComponentField::Float, "Speed", &this->speed));
}

void TestComponent::onUpdate() {
    Orbit::GameObject& gm = getGameObject();
    gm.rotate(Orbit::vec3(0, this->speed, 0));
    if (gm.getRotation().y > 360) {gm.rotate(Orbit::vec3(0,-360, 0));}
    if (gm.getRotation().y < 0) {gm.rotate(Orbit::vec3(0, 360, 0));}
}

void TestComponent::onEnable() {}

void TestComponent::onDisable() {}

void TestComponent::onUnload() {}

