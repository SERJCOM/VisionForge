#pragma once
#include "mesh.hpp"
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

class Object: public Mesh{
public:

    Object(std::vector<glm::vec3> vert, std::vector<glm::vec3> normal, std::vector<glm::vec2> textCoord, std::vector<unsigned int> indices, std::vector<texture> textures);

    void SetupPhysic(PhysicsWorld* physworld, PhysicsCommon* physicsCommon);

    void CreateRigidBody();

    void RotateMesh(float anglex, float angley, float anglez);

    void MoveObject(glm::vec3 position);

    virtual void Draw(Shader& shader){
        glActiveTexture(GL_TEXTURE0);

        unsigned int diffuseNr = 1;
        for (unsigned int i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); 
            std::string number;
            std::string name = textures[i].type;
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            
            glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }

        this->SetMatrix(&shader);
        
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);
    }


protected:

    Physics* phys= nullptr;

    glm::mat4 modelMat;

    void SetMatrix(Shader* shad);

    ~Object();

};