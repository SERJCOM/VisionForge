#pragma once
#include <iostream>
#include "model.h"
#include "mesh.h"
#include "light.h"
#include "shader.h"
#include "texture.h"
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <map>
/// <summary>
/// инструкция пользования классом Object
/// 1)	загрузить модель 
/// 2)	выбрать размер, положение в пространтстве, координаты
/// 3)	
/// </summary>

class Object {
public:
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<texture> textures_loaded;
    std::map <std::string, int> meshNames;
    bool gammaCorrection;

    Object(std::string path, PhysicsWorld* physworld)
    {
        this->physworld = physworld;
        loadModel(path);
    }

    void Draw(Shader& shader)
    {

        for (unsigned int i = 0; i < meshes.size(); i++)
            meshes[i].Draw(shader);
    }

    void SetNewMeshScale(std::string name, glm::vec3 size) {
        meshes[meshNames[name]].meshScale = size;
    }

    void SetNewMeshRotate(std::string name, glm::vec3 rotate) {
        meshes[meshNames[name]].SetNewRotateMesh(rotate);
    }
   

    void SetMeshRotate(std::string name, float angle) {
        meshes[meshNames[name]].RotateMesh(angle);
    }

    void EnablePhysics(bool enable) { this->PhysicBool = enable; }

    static float DegToRad(float angle) {
        return angle * 3.13 / 180;
    }

    /*void SetPhysicsWorld(PhysicsWorld* physworld) { 
        cout << "SetPhysicsWorld\n";
        this->physworld = physworld; 
        cout << "adress1 " << physworld << endl;
    }*/
private:
    bool PhysicBool = true;
    PhysicsWorld* physworld;
    void loadModel(std::string path)
    {
        Assimp::Importer import;
        const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
            return;
        }
        directory = path.substr(0, path.find_last_of('/'));

        processNode(scene->mRootNode, scene);
    }

    void processNode(aiNode* node, const aiScene* scene)
    {

        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            std::cout << node->mName.C_Str() << " " << std::endl;
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(mesh, scene));
            meshNames[node->mName.C_Str()] = i;
            if (PhysicBool == true) {
                meshes[meshes.size() - 1].SetupPhysic(physworld);
                meshes[meshes.size() - 1].CreateRigidBody();
            }
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }
    }

    Mesh processMesh(aiMesh* mesh, const aiScene* scene)
    {

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<texture> textures;


        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            glm::vec3 vector;

            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;

            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;

            if (mesh->mTextureCoords[0])
            {
                glm::vec2 vec;


                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoords = vec;
            }
            else {
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);
            }

            vertices.push_back(vertex);
        }



        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];

            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }





        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];


        std::vector<texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        
        return Mesh(vertices, indices, textures);
    }

    std::vector<texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
    {
        std::vector<texture> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);

            bool skip = false;
            for (unsigned int j = 0; j < textures_loaded.size(); j++)
            {
                if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
                {
                    textures.push_back(textures_loaded[j]);
                    skip = true;
                    break;
                }
            }
            if (!skip)
            {
                texture texturee;
                texturee.id = LoadTextureFromFile(str.C_Str(), this->directory);
                texturee.type = typeName;
                texturee.path = str.C_Str();
                textures.push_back(texturee);
                textures_loaded.push_back(texturee);
            }
        }
        return textures;
    }

};