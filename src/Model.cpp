/*
 * Project: Orbit Engine
 * File: Model.cpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#include <Orbit/Model.hpp>
#include <stdexcept>

namespace Orbit {
    Model::Model(const char *path, bool gamma) : gammaCorrection(gamma) {
        this->loadModel(path);
    }

    void Model::draw() {
        for (auto &mesh : this->meshes)
            mesh.draw(this->shader);
    }

    void Model::loadModel(const char *path) {
        Assimp::Importer importer;
        const unsigned int flags =
                aiProcess_Triangulate |
                aiProcess_GenSmoothNormals |
                aiProcess_FlipUVs |
                aiProcess_CalcTangentSpace;
        const aiScene *scene = importer.ReadFile(path, flags);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            throw std::runtime_error("Cannot load model (ASSIMP): " + std::string(importer.GetErrorString()));
        }
        std::string spath(path);
        directory = spath.substr(0, spath.find_last_of('/'));
        this->processNode(scene->mRootNode, scene);
        importer.FreeScene();
    }

    void Model::processNode(aiNode *node, const aiScene *scene) {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            this->meshes.push_back(processMesh(mesh, scene));
        }
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            processNode(node->mChildren[i], scene);
        }
    }

    Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture *> textures;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            Vertex vertex{};
            vec3 vector;

            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.position = vector;

            if (mesh->HasNormals()) {
                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex.normal = vector;
            }
            if (mesh->mTextureCoords[0]) {
                glm::vec2 vec;

                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.texCoords = vec;

                vector.x = mesh->mTangents[i].x;
                vector.y = mesh->mTangents[i].y;
                vector.z = mesh->mTangents[i].z;
                vertex.tangent = vector;

                vector.x = mesh->mBitangents[i].x;
                vector.y = mesh->mBitangents[i].y;
                vector.z = mesh->mBitangents[i].z;
                vertex.bitangent = vector;
            } else
                vertex.texCoords = vec2(0.0f, 0.0f);

            vertices.push_back(vertex);
        }
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        // 1. diffuse maps
        std::vector<Texture *> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE,
                                                                  Texture::TEX_DIFFUSE);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. specular maps
        std::vector<Texture *> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR,
                                                                   Texture::TEX_SPECULAR);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        // 3. normal maps
        std::vector<Texture *> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, Texture::TEX_NORMAL);
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        // 4. height maps
        std::vector<Texture *> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, Texture::TEX_HEIGHT);
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

        return Mesh(vertices, indices, textures);
    }

    std::vector<Texture *> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, Texture::Type typeName) {
        std::vector<Texture *> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
            aiString str;
            mat->GetTexture(type, i, &str);
            bool skip = false;
            for (auto &j : textures_loaded) {
                if (std::strcmp(std::string(j->path).data(), str.C_Str()) == 0) {
                    textures.push_back(j);
                    skip = true;
                    break;
                }
            }
            if (!skip) {
                Texture *texture = new Texture((this->directory + '/' + std::string(str.C_Str())).c_str());
                texture->type = typeName;
                textures.push_back(texture);
                textures_loaded.push_back(texture);
            }
        }
        return textures;
    }
}