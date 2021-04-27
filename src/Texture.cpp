/*
 * Project: Orbit Engine
 * File: Texturecpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#include <Orbit/Texture.hpp>
#include <Orbit/stb_image.h>
#include <stdexcept>
#include <cstring>
#include <glad/glad.h>

namespace Orbit {

    Texture::Texture(const char *path) {
        int width, height, channels;
        bool isPNG = false;
        if (strlen(path) > 4) {
            const char *end = path + (strlen(path) - 4);
            if (strcmp(end, ".png") == 0)
                isPNG = true;
        }
        this->path = path;
        glGenTextures(1, &this->textureId);
        glBindTexture(GL_TEXTURE_2D, this->textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
        if (!data)
            throw std::runtime_error(std::string("Cannot load texture: ") + path);
        this->width = width;
        this->height = height;
        glTexImage2D(GL_TEXTURE_2D, 0, isPNG ? GL_RGBA : GL_RGB, width, height, 0, isPNG ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }

    unsigned int Texture::getTextureId() const {
        return this->textureId;
    }

}