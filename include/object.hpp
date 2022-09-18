#pragma once
//#include "mesh.hpp"
#include <reactphysics3d/reactphysics3d.h> 
#include <assimp/mesh.h>

using namespace reactphysics3d;

struct Physics{
    glm::vec3 meshScale = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 angleRotate = glm::vec3(0.0f, 0.0f, 0.0f);
    Quaternion orientation = Quaternion::fromEulerAngles(0, 0, 0);
    glm::vec3 meshPosition = glm::vec3(0.0f, 0.0f, 0.0f);

    PhysicsCommon* physicsCommon;
    PhysicsWorld* world;
    RigidBody* body;

    bool physicsEnable = false;
};

class Object{
public:
    std::vector<glm::vec3> verticles;
    std::vector<glm::vec3> normal;
    std::vector<unsigned int> indices;
    std::vector<glm::vec2> textCoord;
    std::vector<texture> textures;

    unsigned int VAO, VBO, EBO;

    Object(std::vector<glm::vec3> vert, std::vector<glm::vec3> normal, std::vector<glm::vec2> textCoord, std::vector<unsigned int> indices, std::vector<texture> textures);

    void SetupPhysic(PhysicsWorld* physworld, PhysicsCommon* physicsCommon);

    void CreateRigidBody();

    void RotateMesh(float anglex, float angley, float anglez);

    void SetRotateMesh(float anglex, float angley, float anglez);

    void MoveObject(glm::vec3 position);

    void SetObjectPosition(glm::vec3 position);

    virtual void Draw(Shader& shader);

    ~Object();

protected:

    Physics phys;

    glm::mat4 modelMat;

    void SetMatrix(Shader* shad);

    virtual void setupMesh();

};