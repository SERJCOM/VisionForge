#include "object.hpp"

Object::Object(std::vector<glm::vec3> vert, std::vector<glm::vec3> normal, std::vector<glm::vec2> textCoord, std::vector<unsigned int> indices, std::vector<texture> textures){
    Mesh::Mesh(vert, normal, textCoord, indices, textures);
    phys = new Physics;
}

Object::~Object(){
    delete phys;
}

void Object::SetMatrix(Shader* shad) {
    Quaternion orientation;
    Vector3 position;
    if (phys->physicsEnable) {
        Transform transform = phys->body->getTransform();
        position = transform.getPosition();
        orientation = transform.getOrientation();
    }
    else {
        orientation = Quaternion::fromEulerAngles(phys->angleRotate.x, phys->angleRotate.y, phys->angleRotate.z);
        position = Vector3(phys->meshPosition.x, phys->meshPosition.y, phys->meshPosition.z);
    }
    glm::vec4 orient[3];
    glm::mat4 orientMat;
    for (int i = 0; i < 3; i++) {
        orient[i].x = phys->orientation.getMatrix().getRow(i).x;
        orient[i].y = phys->orientation.getMatrix().getRow(i).y;
        orient[i].z = phys->orientation.getMatrix().getRow(i).z;
        orient[i].w = 0;
    }
    orientMat = glm::mat4(orient[0].x, orient[0].y, orient[0].z, orient[0].w,
        orient[1].x, orient[1].y, orient[1].z, orient[1].w,
        orient[2].x, orient[2].y, orient[2].z, orient[2].w,
        0.0, 0.0, 0.0, 1.0);
    modelMat = glm::mat4(1);
    modelMat = glm::translate(modelMat, glm::vec3(position.x, position.y, position.z));
    modelMat = modelMat * orientMat;
    modelMat = glm::scale(modelMat, phys->meshScale);
    
    shad->setMat4("model", modelMat);
}


void Object::SetupPhysic(PhysicsWorld* physworld, PhysicsCommon* physicsCommon) {
    this->phys->world = physworld;
    this->phys->physicsCommon = physicsCommon;
    phys->physicsEnable = true;
}

void Object::CreateRigidBody(){
    Vector3 position(phys->meshPosition.x, phys->meshPosition.y, phys->meshPosition.z);
    Quaternion orientation = Quaternion::fromEulerAngles(glm::radians(phys->angleRotate.x), glm::radians(phys->angleRotate.y), glm::radians(phys->angleRotate.z));
    Transform transform(position, orientation);
    phys->body = phys->world->createRigidBody(transform);
    phys->body->setType(BodyType::KINEMATIC);
}

void Object::RotateMesh(float anglex, float angley, float anglez) {
    phys->angleRotate.x += anglex;
    phys->angleRotate.y += angley;
    phys->angleRotate.z += anglez;
    if (phys->physicsEnable) {
        Transform currentTransform = phys->body->getTransform();
        Quaternion orientation = currentTransform.getOrientation();
        orientation = Quaternion::fromEulerAngles(phys->angleRotate.x, phys->angleRotate.y, phys->angleRotate.z);
        currentTransform.setOrientation(orientation);
        phys->body->setTransform(currentTransform);
    }
}

void Object::MoveObject(glm::vec3 position) {
    phys->meshPosition += position;
    if (phys->physicsEnable) {
        Transform currentTransform = phys->body->getTransform();
        Vector3 pos;
        pos.setAllValues(phys->meshPosition.x, phys->meshPosition.y, phys->meshPosition.z);
        currentTransform.setPosition(pos);
        phys->body->setTransform(currentTransform);
    }
}

