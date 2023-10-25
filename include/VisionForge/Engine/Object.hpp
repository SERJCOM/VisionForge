#pragma once
#include "VisionForge/Engine/Mesh.hpp"
#include <reactphysics3d/reactphysics3d.h>
#include <assimp/mesh.h>

using namespace reactphysics3d;

struct Physics
{
    glm::vec3 meshScale = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 angleRotate = glm::vec3(0.0f, 0.0f, 0.0f);
    Quaternion orientation = Quaternion::fromEulerAngles(0, 0, 0);
    glm::vec3 meshPosition = glm::vec3(0.0f, 0.0f, 0.0f);

    PhysicsCommon *physicsCommon;
    PhysicsWorld *world;
    RigidBody *body;

    bool physicsEnable = false;
};

class Object : public Mesh
{
public:
    Object(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<sTexture> textures);

    void SetupPhysic(PhysicsWorld *physworld, PhysicsCommon *physicsCommon);

    void CreateRigidBody();

    void ScaleMesh(glm::vec3 size);

    void RotateMesh(float anglex, float angley, float anglez);

    void SetMeshRotation(float anglex, float angley, float anglez);

    void MoveObject(glm::vec3 position);

    void SetObjectPosition(glm::vec3 position);

    virtual void Draw(Shader &shader);

    void bodyAddColiderBox(glm::vec3 halfsize);

    ~Object();

protected:
    Physics phys;

    glm::mat4 modelMat;

    void SetMatrix(Shader *shad);

    virtual void setupMesh();
};