/*
 * Project: Orbit Engine
 * File: Runtime.hpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#ifndef ORBITENGINE_RUNTIME_HPP
#define ORBITENGINE_RUNTIME_HPP

#include <Orbit/Window.hpp>
#include <Orbit/Scene.hpp>

namespace Orbit {
    class Runtime {
    public:
        static void execute(Window *window);
        static void setRenderResolution(vec2 res);
        static const vec2 &getRenderResolution();

    private:
        explicit Runtime() = default;
        static void render(Window *window);

        inline static Scene *scene = nullptr;
        inline static vec2 renderResolution;
    };
}

#endif //ORBITENGINE_RUNTIME_HPP
