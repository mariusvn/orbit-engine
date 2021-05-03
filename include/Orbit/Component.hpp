/*
 * Project: Orbit Engine
 * File: Component.hpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#ifndef ORBITENGINE_COMPONENT_HPP
#define ORBITENGINE_COMPONENT_HPP

#include <string>
#include <vector>
#include <Orbit/ComponentField.hpp>

namespace Orbit {

    class GameObject;

    class Component {
    public:
        explicit Component(const char *name): name(name) {};
        ~Component() = default;

        std::vector<ComponentField*> fields {};

        /**
         * Called on scene initialization, before onEnable and onUpdate
         */
        virtual void onInit() = 0;
        /**
         * Called on the game loop while the component is enabled
         */
        virtual void onUpdate() = 0;
        /**
         * Called on component enabling and just after init()
         */
        virtual void onEnable() = 0;
        /**
         * Called on component disabling and before onUnload()
         */
        virtual void onDisable() = 0;
        /**
         * Called on component unloading, this is the last
         * function called in the lifecycle
         */
        virtual void onUnload() = 0;

        void assignGameObject(GameObject* gm);

        virtual const std::string &getComponentName() const final;
        virtual bool isEnabled() const final;
        virtual void enable() final;
        virtual void disable() final;
        const std::string name;

    protected:
        virtual GameObject &getGameObject() const final;

    private:
        GameObject *gameObject = nullptr;
        bool isComponentEnabled = true;
    };
}

#endif //ORBITENGINE_COMPONENT_HPP
