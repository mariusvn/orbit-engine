/*
 * Project: Orbit Engine
 * File: Model.hpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#ifndef ORBITENGINE_MODEL_HPP
#define ORBITENGINE_MODEL_HPP

#include <Orbit/Shader.hpp>
#include <Orbit/Texture.hpp>
#include <Orbit/Mesh.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <string>

namespace Orbit {
    class Model {
    public:
        std::vector<Texture *> textures_loaded;
        std::vector<Mesh> meshes;
        std::string directory;
        Shader *shader = Shader::getStandardShader();
        bool gammaCorrection;

        explicit Model(const char *path, bool gamma = false);
        void draw();

    protected:
        virtual void loadModel(const char *path);


    private:
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture *> loadMaterialTextures(aiMaterial *mat, aiTextureType type, Texture::Type typeName);
    };
}

#endif //ORBITENGINE_MODEL_HPP
