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
#include "VisionForge/EntitySystem/VisualComponent.hpp"
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

    class ModelComponent : public IVisualComponent
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
            // Draw();
        }

        void Draw(Shader& shader) override;

        void LoadModel();

        void AddMaterial(Material *mat);

        void SetPath(std::filesystem::path path);

        void ScaleObject(glm::vec3 size) override{
            Object::ScaleObject(size);

            ProcessMesh([size](Mesh& mesh){
                mesh.ScaleObject(size);
            });
        }

        void SetObjectSize(glm::vec3 size) override{
            Object::SetObjectSize(size);

            ProcessMesh([size](Mesh& mesh){
                mesh.SetObjectSize(size);
            });
        }

        void SetObjectPosition(glm::vec3 pos) override{
            Object::SetObjectPosition(pos);

            ProcessMesh([pos](Mesh& mesh){
                mesh.SetObjectPosition(pos);
            });            
        }

        void MoveObject(glm::vec3 pos) override {
            Object::MoveObject(pos);

            ProcessMesh([pos](Mesh& mesh){
                mesh.MoveObject(pos);
            });  
        }

        void SetObjectRotation(double angle, glm::vec3 axis) override{
            Object::SetObjectRotation(angle, axis);

            ProcessMesh([angle, axis](Mesh& mesh){
                mesh.SetObjectRotation(angle, axis);
            });  
        }


        static float DegToRad(float angle)
        {
            return static_cast<float>(angle) * 3.13f / 180.0f;
        }

    protected:

        template<typename T>
        void ProcessMesh(T func){
            for(auto& mesh : meshes){
                func(mesh);
            }
        }


        int number = 0;
        std::string path;

        std::string rootName;

        std::vector<Mesh> meshes;
        std::string directory;
        std::vector<sTexture> textures_loaded;
        std::unordered_map<std::string, int> meshNames;

        Material *_material = nullptr;


        void LoadModel(std::string path);

        void processNode(aiNode *node, const aiScene *scene, int index);

        Mesh processMesh(aiMesh *mesh, const aiScene *scene);

        std::vector<sTexture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    };

}