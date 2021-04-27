/*
 * Project: Orbit Engine
 * File: Shader.cpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#include <Orbit/Shader.hpp>
#include <iostream>
#include <fstream>
#include <cstring>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <Orbit/Logger.hpp>

namespace Orbit {

    Shader::Shader(const char *vcontent, const char *fcontent) {
        this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
        this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        this->shaderProgram = glCreateProgram();

        glShaderSource(this->vertexShader, 1, &vcontent, nullptr);
        glCompileShader(this->vertexShader);
        Shader::checkCompileStatus(this->vertexShader, GL_COMPILE_STATUS);

        glShaderSource(this->fragmentShader, 1, &fcontent, nullptr);
        glCompileShader(this->fragmentShader);
        Shader::checkCompileStatus(this->fragmentShader, GL_COMPILE_STATUS);

        glAttachShader(this->shaderProgram, this->vertexShader);
        glAttachShader(this->shaderProgram, this->fragmentShader);
        glLinkProgram(this->shaderProgram);
        Shader::checkCompileStatus(this->shaderProgram, GL_LINK_STATUS);
    }

    Shader *Shader::loadFromFiles(const char *vertex, const char *fragment) {
        const char *vertex_content = Shader::readFile(vertex);
        const char *fragment_content = Shader::readFile(fragment);
        auto* shader = new Shader(vertex_content, fragment_content);
        delete vertex_content;
        delete fragment_content;
        return shader;
    }

    const char *Shader::readFile(const char *path) {
        std::ifstream stream(path);
        std::string content(std::istreambuf_iterator<char>(stream),(std::istreambuf_iterator<char>()));
        return strdup(content.c_str());
    }

    Shader *Shader::loadFromMemory(const char *vertex_content, const char *fragment_content) {
        return new Shader(vertex_content, fragment_content);
    }

    unsigned int Shader::getShaderProgram() const {
        return this->shaderProgram;
    }

    void Shader::checkCompileStatus(unsigned int target, GLenum type) {
        int success;
        glGetShaderiv(target, type, &success);
        if (!success) {
            char infoLog[1024];
            glGetShaderInfoLog(target, 1024, nullptr, infoLog);
            error("Error while compiling shader:", infoLog);
            throw std::runtime_error("Error while compiling shader");
        }
    }

    Shader *Shader::getStandardShader() {
        if (Shader::standardShader == nullptr) {
            Shader::standardShader = Shader::loadFromFiles("shaders/standard/vertex.glsl", "shaders/standard/fragment.glsl");
        }
        return Shader::standardShader;
    }

    void Shader::use() {
        glUseProgram(this->shaderProgram);
    }

    void Shader::set(const char *name, float data) {
        glUniform1f(glGetUniformLocation(this->shaderProgram, name), data);
    }

    void Shader::set(const char *name, int data) {
        glUniform1i(glGetUniformLocation(this->shaderProgram, name), data);
    }

    void Shader::set(const char *name, mat4 matrix) {
        glUniformMatrix4fv(glGetUniformLocation(this->shaderProgram, name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Shader::set(const char *name, vec3 vec) {
        glUniform3f(glGetUniformLocation(this->shaderProgram, name), vec.x, vec.y, vec.z);
    }

    void Shader::set(const char *name, unsigned int data) {
        this->set(name, (int) data);
    }
}