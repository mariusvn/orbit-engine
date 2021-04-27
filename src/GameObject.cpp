/*
 * Project: Orbit Engine
 * File: GameObjectcpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#include <Orbit/GameObject.hpp>

namespace Orbit {
    void GameObject::draw(mat4 parentTransform) {
        mat4 transform = parentTransform * this->getTransformMatrix();
        this->model->shader->use();
        this->model->shader->set("transform", transform);
        this->model->draw();
        for (int i = 0; i < this->children.size(); i++)
            children[i]->draw(transform);
    }
}