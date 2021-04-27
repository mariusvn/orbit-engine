/*
 * Project: Orbit Engine
 * File: Shader.hpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#ifndef ORBITENGINE_SHADER_HPP
#define ORBITENGINE_SHADER_HPP

#include <Orbit/Types.hpp>

namespace Orbit {
    class Shader {
    public:
        static Shader* loadFromFiles(const char* vertex, const char* fragment);
        static Shader* loadFromMemory(const char* vertex_content, const char* fragment_content);
        static Shader* getStandardShader();

        void use();
        void set(const char *name, float data);
        void set(const char *name, int data);
        void set(const char *name, mat4 matrix);
        void set(const char *name, vec3 vec);
        void set(const char *name, unsigned int data);
        unsigned int getShaderProgram() const;

    private:
        explicit Shader(const char* vcontent, const char* fcontent);

        static const char *readFile(const char *path);
        static void checkCompileStatus(unsigned int target, unsigned int type);
        inline static Shader* standardShader = nullptr;

        unsigned int vertexShader = 0;
        unsigned int fragmentShader = 0;
        unsigned int shaderProgram = 0;
    };
}

#endif //ORBITENGINE_SHADER_HPP
