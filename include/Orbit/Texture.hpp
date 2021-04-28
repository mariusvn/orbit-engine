/*
 * Project: Orbit Engine
 * File: Texture.hpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#ifndef ORBITENGINE_TEXTURE_HPP
#define ORBITENGINE_TEXTURE_HPP

namespace Orbit {
    class Texture {
    public:
        explicit Texture(const char *path);
        unsigned int getTextureId() const;

        enum Type {
            TEX_DIFFUSE = 1,
            TEX_SPECULAR = 2,
            TEX_NORMAL = 4,
            TEX_HEIGHT = 8
        };

        Type type = TEX_DIFFUSE;
        const char *path;

    private:
        unsigned int textureId = 0;
        unsigned int width = 0;
        unsigned int height = 0;
    };
}

#endif //ORBITENGINE_TEXTURE_HPP
