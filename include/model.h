#pragma once
#include <iostream>
#include "object.hpp"
#include "light.h"
#include "shader.h"
#include "Texture.h"
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <map>
#include <vector>

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



class Model {
public:
    std::vector<Object> meshes;
    std::string directory;
    std::vector<sTexture> textures_loaded;
    std::map <std::string, int> meshNames;
    bool gammaCorrection;


    Model(std::string path, PhysicsWorld* physworld, PhysicsCommon* physicsCommon);

    Model(const char* path, PhysicsWorld* physworld, PhysicsCommon* physicsCommon);

    void Draw(Shader& shader);

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
        delete triangleArray;
    }
protected:
    bool PhysicBool = true;
    int number = 0;

    std::string rootName;
    PhysicsCommon* physicsCommon;
    PhysicsWorld* physworld;
    RigidBody* body = nullptr;

    glm::vec3 objectPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 objectAngleRotate = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 objectScale = glm::vec3(1.0f, 1.0f, 1.0f);


    // concave collision 
    TriangleVertexArray* triangleArray = nullptr;
    TriangleMesh* triangleMesh = nullptr;
    ConcaveMeshShape* concaveMesh = nullptr;
    Vector3 size_object;
    // end concave collision

    //sBoundingBox modelBoundingBox;

    void loadModel(std::string path);

    void processNode(aiNode* node, const aiScene* scene, int index);

    Object processMesh(aiMesh* mesh, const aiScene* scene);

    std::vector<sTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

};

