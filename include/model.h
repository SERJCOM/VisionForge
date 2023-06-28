#pragma once
#include <iostream>
#include "object.hpp"
#include "lightManager.hpp"
#include "Shader.h"
#include "Texture.h"
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <map>
#include <vector>
#include <map>
#include "material.hpp"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct sConcaveMesh{
    TriangleVertexArray* triangleArray = nullptr;
    TriangleMesh* triangleMesh = nullptr;
    ConcaveMeshShape* concaveMesh = nullptr;
};


struct sMeshParameters{
    std::vector<glm::vec3> meshPosition;
    std::vector<glm::vec3> meshOrientation;
    std::vector<glm::vec3> meshScale;
};

class Model {
public:
    std::vector<Object> meshes;
    std::string directory;
    std::vector<sTexture> textures_loaded;
    std::map <std::string, int> meshNames;
    bool gammaCorrection;


    Model(std::string path);

    Model(const char* path);

    void Draw(Shader& shader);

    void LoadModel();

    void AddMaterial(Li::Material* mat);

    void SetPath(std::string path);

    void ScaleMesh(std::string name, glm::vec3 size);

    void ScaleObject(glm::vec3 size);

    void RotateMesh(std::string name, float anglex, float angley, float anglez);

    void RotateObject(float anglex, float angley, float anglez);

    void RotateObject(glm::vec3 angles);

    void SetMeshRotation(std::string name, float anglex, float angley, float anglez);
                        
    void SetObjectRotation(float anglex, float angley, float anglez);

    void SetObjectRotation(glm::vec3 rot);

    void MoveObject(float x, float y, float z);

    void MoveMesh(std::string name, float x, float y, float z);

    void SetMeshPosition(std::string name, float x, float y, float z);

    void SetObjectPosition(float x, float y, float z);

    void EnablePhysics(bool enable) { this->PhysicBool = enable; }

    static float DegToRad(float angle) {
        return static_cast<float>(angle) * 3.13f / 180.0f;
    }

    void SetupPhysicMeshByName(std::string name);

    void CreatePhysicsBody();

    void CreateCollisionBox(glm::vec3 halfExtents);

    void CreateCollisionSphere(float radius);

    void CreateCollisionCapsule(glm::vec2 halfSize);

    void CreateConcaveMeshShape();

    void SetTypeOfThePhysObject(bool flag);

    void UpdateObjectTransform();

    void PrintObjectPosition();

    ~Model(){
        for(int i = 0; i < concavemesh.size(); i++)
            delete concavemesh[i].triangleArray;
    }
protected:
    bool                PhysicBool = true;
    int                 number = 0;
    std::string         path;

    std::string         rootName;
    PhysicsCommon*      physicsCommon;
    PhysicsWorld*       physworld;
    RigidBody*          body = nullptr;

    glm::vec3           objectPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3           objectAngleRotate = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3           objectScale = glm::vec3(1.0f, 1.0f, 1.0f);

    std::vector<sConcaveMesh> concavemesh;

    Li::Material            *_material = nullptr;

    //std::map<std::string, sMeshParameters> MeshParameters;

    std::vector<int>    changedMeshes;

    void LoadModel(std::string path);

    void processNode(aiNode* node, const aiScene* scene, int index);

    Object processMesh(aiMesh* mesh, const aiScene* scene);

    std::vector<sTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

