/*
 * Project: Orbit Engine
 * File: Texture.cpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

// NOTE(marius): STB implementation, do not remove the define
#define STB_IMAGE_IMPLEMENTATION

#include <Orbit/stb_image.h>

#include <Orbit/Texture.hpp>
#include <stdexcept>
#include <cstring>
#include <glad/glad.h>

namespace Orbit {

    Texture::Texture(const char *path) {
        int imgWidth, imgHeight, imgChannels;
        bool isPNG = false;
        unsigned char *data;

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

        data = stbi_load(path, &imgWidth, &imgHeight, &imgChannels, 0);
        if (!data)
            throw std::runtime_error(std::string("Cannot load texture: ") + path);

        this->width = imgWidth;
        this->height = imgHeight;

        glTexImage2D(GL_TEXTURE_2D, 0, isPNG ? GL_RGBA : GL_RGB, imgWidth, imgHeight, 0, isPNG ? GL_RGBA : GL_RGB,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }

    unsigned int Texture::getTextureId() const {
        return this->textureId;
    }

}