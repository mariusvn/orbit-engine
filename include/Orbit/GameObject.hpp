/*
 * Project: Orbit Engine
 * File: GameObject.hpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#ifndef ORBITENGINE_GAMEOBJECT_HPP
#define ORBITENGINE_GAMEOBJECT_HPP

#include <Orbit/Component.hpp>
#include <Orbit/Model.hpp>
#include <vector>
#include <glad/glad.h>
#include <Orbit/Types.hpp>
#include <Orbit/Transformable.hpp>

namespace Orbit {

    class GameObject : public Transformable {
    public:
        std::vector<GameObject *> children{};
        std::vector<Component *> components{};
        std::string name = "GameObject";
        Model *model = nullptr;

        void draw(mat4 parentTranformMatrix);

    };

}

#endif //ORBITENGINE_GAMEOBJECT_HPP
