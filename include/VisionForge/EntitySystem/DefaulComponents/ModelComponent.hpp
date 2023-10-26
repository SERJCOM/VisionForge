#pragma once
#include <iostream>
#include "VisionForge/Engine/Object.hpp"

#include "VisionForge/System/Shader.hpp"
#include "VisionForge/Common/Texture.hpp"
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <map>
#include <vector>
#include <unordered_map>
#include "VisionForge/Engine/Material.hpp"
#include "VisionForge/EntitySystem/Component.hpp"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace vision
{

    struct sConcaveMesh
    {
        TriangleVertexArray *triangleArray = nullptr;
        TriangleMesh *triangleMesh = nullptr;
        ConcaveMeshShape *concaveMesh = nullptr;
    };

    struct sMeshParameters
    {
        std::vector<glm::vec3> meshPosition;
        std::vector<glm::vec3> meshOrientation;
        std::vector<glm::vec3> meshScale;
    };

    class ModelComponent : public IComponent
    {
    public:
        std::vector<Object> meshes;
        std::string directory;
        std::vector<sTexture> textures_loaded;
        std::unordered_map<std::string, int> meshNames;
        bool gammaCorrection;

        ModelComponent(std::string path);

        ModelComponent(const char *path);

        void Start() override
        {
        }

        void Update() override
        {
            Draw(*shader_);
        }

        void Draw(Shader &shader);

        void SetShader(Shader &shader)
        {
            shader_ = &shader;
        }

        void LoadModel();

        void AddMaterial(Li::Material *mat);

        void SetPath(std::string path);

        void ScaleObject(glm::vec3 size);

        void RotateObject(float anglex, float angley, float anglez);

        void RotateObject(glm::vec3 angles);

        void SetObjectRotation(float anglex, float angley, float anglez);

        void SetObjectRotation(glm::vec3 rot);

        void MoveObject(float x, float y, float z);

        static float DegToRad(float angle)
        {
            return static_cast<float>(angle) * 3.13f / 180.0f;
        }

        ~ModelComponent()
        {
            for (int i = 0; i < concavemesh.size(); i++)
                delete concavemesh[i].triangleArray;
        }

    protected:
        Shader *shader_;

        bool PhysicBool = true;
        int number = 0;
        std::string path;

        std::string rootName;

        glm::vec3 objectPosition = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 objectAngleRotate = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 objectScale = glm::vec3(1.0f, 1.0f, 1.0f);

        std::vector<sConcaveMesh> concavemesh;

        Li::Material *_material = nullptr;

        std::vector<int> changedMeshes;

        void LoadModel(std::string path);

        void processNode(aiNode *node, const aiScene *scene, int index);

        Object processMesh(aiMesh *mesh, const aiScene *scene);

        std::vector<sTexture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    };

}