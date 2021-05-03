/*
 * Project: Orbit Engine
 * File: Terrain.hpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#ifndef ORBITENGINE_TERRAIN_HPP
#define ORBITENGINE_TERRAIN_HPP

#include <Orbit/Model.hpp>

namespace Orbit {
    class Terrain : public Model {
    public:
        explicit Terrain(vec<2, unsigned short> precision, vec<2, float> size);
    protected:
        void loadModel(const char *path) override;
        vec<2, unsigned short> precision = vec<2, unsigned short>(0,0);
        vec<2, float> size = vec<2, float>(0,0);

    private:
        int getCoord(ivec2 pos, ivec2 size) const;

    };
}

#endif //ORBITENGINE_TERRAIN_HPP
