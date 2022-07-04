#pragma once

#include <iostream>
#include <reactphysics3d/reactphysics3d.h> 
#include "shader.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace reactphysics3d;

struct Vertex {
    glm::vec3 Position;
    glm::vec2 TexCoords;
    glm::vec3 Normal;
};

struct texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
public:
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<texture> textures;
    glm::mat4 model;
    glm::vec3 PhysicPosition;
    glm::vec3 ColliderSize;

    glm::vec3 meshScale = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 angleRotate = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 meshPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    float angle = 0;
   

    PhysicsWorld* world;
    RigidBody* body;
    bool AlwaysUpdateMatrix = true; 
    

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<texture> textures){
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;
        setupMesh();
    }

    

    void SetupPhysic(PhysicsWorld* physworld) {
        this->world = physworld;
    }
    void CreateRigidBody(){
        
        //Vector3 position(PhysicPosition.x, PhysicPosition.y, PhysicPosition.z);
        Vector3 position(meshPosition.x, meshPosition.y, meshPosition.z);
        Quaternion orientation = Quaternion::identity();
        Transform transform(position, orientation);
        
        body = world->createRigidBody(transform);
        body->setType(BodyType::KINEMATIC);
    }


    void RotateMesh(float anglex, float angley, float anglez) {
        angleRotate.x += anglex;
        angleRotate.y += angley;
        angleRotate.z += anglez;
        Transform currentTransform = body->getTransform();
        Quaternion orientation = currentTransform.getOrientation();
        orientation = Quaternion::fromEulerAngles(angleRotate.x, angleRotate.y, angleRotate.z);
        currentTransform.setOrientation(orientation);
        body->setTransform(currentTransform); 
    }

    void MoveObject(glm::vec3 position) {
        meshPosition += position;
        Transform currentTransform = body->getTransform();
        Vector3 pos;
        pos.setAllValues(meshPosition.x, meshPosition.y, meshPosition.z);
        currentTransform.setPosition(pos);
        body->setTransform(currentTransform);
    }

    void SetObjectPosition(glm::vec3 position) {
        meshPosition = glm::vec3(0.0f);
        MoveObject(position);
    }

    void CreateCollider(PhysicsCommon &physicsCommon) {
        Vector3 halfExtents(ColliderSize.x, ColliderSize.y, ColliderSize.z);
        BoxShape* boxShape = physicsCommon.createBoxShape(halfExtents);
        Transform transform = Transform::identity();
        collider = body->addCollider(boxShape, transform);
    }

    void ObjectKinematic(bool paramert) {
        if (paramert)    body->setType(BodyType::KINEMATIC);
        else    body->setType(BodyType::DYNAMIC);
    }

    void SetMatrix(Shader* shad) {
        Transform transform = body->getTransform();
        Vector3 position = transform.getPosition();
        Quaternion orientation = transform.getOrientation();
        glm::vec4 orient[3];
        glm::mat4 orientMat;
        for (int i = 0; i < 3; i++) {
            orient[i].x = orientation.getMatrix().getRow(i).x;
            orient[i].y = orientation.getMatrix().getRow(i).y;
            orient[i].z = orientation.getMatrix().getRow(i).z;
            orient[i].w = 0;
        }
        orientMat = glm::mat4(orient[0].x, orient[0].y, orient[0].z, orient[0].w,
            orient[1].x, orient[1].y, orient[1].z, orient[1].w,
            orient[2].x, orient[2].y, orient[2].z, orient[2].w,
            0.0, 0.0, 0.0, 1.0);
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(position.x, position.y, position.z));
        model =  model * orientMat;
        model = glm::scale(model, meshScale);
        shad->setMat4("model", model);
    }

    void Draw(Shader shader) {     
        //cout << meshRotate.x << " " << meshRotate.y << " " << meshRotate.z << endl;
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
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);
    }

private:
    unsigned int VAO, VBO, EBO;
    
    Collider* collider;
    Shader* shader;

    void setupMesh(){
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
            &indices[0], GL_STATIC_DRAW);

        
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
        

        glBindVertexArray(0);
    }
};




