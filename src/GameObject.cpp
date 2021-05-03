/*
 * Project: Orbit Engine
 * File: GameObject.cpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#include <Orbit/GameObject.hpp>

namespace Orbit {
    void GameObject::draw(mat4 parentTransform) {
        mat4 transform = parentTransform * this->getTransformMatrix();
        if (this->model && this->model->shader) {
            this->model->shader->use();
            this->model->shader->set("transform", transform);
            this->model->draw();
        }
        for (int i = 0; i < this->children.size(); i++)
            children[i]->draw(transform);
    }

    void GameObject::update() {
        for (Component *comp : this->components) {
            if (comp->isEnabled())
                comp->onUpdate();
        }
        for (GameObject *gm : this->children) {gm->update();}
    }

    void GameObject::init() {
        for (Component *comp : this->components) {comp->onInit();}
        for (Component *comp : this->components) {comp->onEnable();}
        for (GameObject *gm : this->children) {gm->init();}
    }

    void GameObject::unload() {
        for (Component *comp : this->components) {comp->onDisable();}
        for (Component *comp : this->components) {comp->onUnload();}
        for (GameObject *gm : this->children) {gm->unload();}
    }
}