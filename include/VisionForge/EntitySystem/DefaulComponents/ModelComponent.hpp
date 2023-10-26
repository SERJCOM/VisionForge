#pragma once
#include <iostream>

#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <map>
#include <vector>
#include <unordered_map>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <filesystem>

#include "VisionForge/Engine/Material.hpp"
#include "VisionForge/EntitySystem/Component.hpp"
#include "VisionForge/System/Shader.hpp"
#include "VisionForge/Common/Texture.hpp"
#include "VisionForge/Engine/Mesh.hpp"
#include "VisionForge/Engine/Engine.hpp"

namespace vision
{


    struct sMeshParameters
    {
        std::vector<glm::vec3> meshPosition;
        std::vector<glm::vec3> meshOrientation;
        std::vector<glm::vec3> meshScale;
    };

    class ModelComponent : public IComponent
    {
    public:
        
        ModelComponent(std::string path);

        ModelComponent(const char *path);

        ModelComponent(){}

        void Start() override
        {
        }

        void Update() override
        {
            Draw();
        }

        void Draw();


        void LoadModel();

        void AddMaterial(Material *mat);

        void SetPath(std::filesystem::path path);

        

        static float DegToRad(float angle)
        {
            return static_cast<float>(angle) * 3.13f / 180.0f;
        }

    protected:

        int number = 0;
        std::string path;

        std::string rootName;

        std::vector<Mesh> meshes;
        std::string directory;
        std::vector<sTexture> textures_loaded;
        std::unordered_map<std::string, int> meshNames;
        bool gammaCorrection;

        Material *_material = nullptr;

        std::vector<int> changedMeshes;

        void LoadModel(std::string path);

        void processNode(aiNode *node, const aiScene *scene, int index);

        Mesh processMesh(aiMesh *mesh, const aiScene *scene);

        std::vector<sTexture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    };

}