#include "object.hpp"

Object::Object(std::vector<glm::vec3> vert, std::vector<glm::vec3> normal, std::vector<glm::vec2> textCoord, std::vector<unsigned int> indices, std::vector<texture> textures):
Mesh(vert, normal, textCoord, indices, textures){

    this->setupMesh();
    //phys = new Physics;
}

Object::~Object(){
    //delete phys;
}

void Object::SetMatrix(Shader* shad){
    Quaternion orientation;
    Vector3 position;
    if (phys.physicsEnable) {
        Transform transform = phys.body->getTransform();
        position = transform.getPosition();
        orientation = transform.getOrientation();
    }
    else {
        orientation = Quaternion::fromEulerAngles(phys.angleRotate.x, phys.angleRotate.y, phys.angleRotate.z);
        position = Vector3(phys.meshPosition.x, phys.meshPosition.y, phys.meshPosition.z);
    }
    glm::vec4 orient[3];
    glm::mat4 orientMat;
    for (int i = 0; i < 3; i++) {
        orient[i].x = phys.orientation.getMatrix().getRow(i).x;
        orient[i].y = phys.orientation.getMatrix().getRow(i).y;
        orient[i].z = phys.orientation.getMatrix().getRow(i).z;
        orient[i].w = 0;
    }
    orientMat = glm::mat4(orient[0].x, orient[0].y, orient[0].z, orient[0].w,
        orient[1].x, orient[1].y, orient[1].z, orient[1].w,
        orient[2].x, orient[2].y, orient[2].z, orient[2].w,
        0.0, 0.0, 0.0, 1.0);
    modelMat = glm::mat4(1);
    modelMat = glm::translate(modelMat, glm::vec3(position.x, position.y, position.z));
    modelMat = modelMat * orientMat;
    modelMat = glm::scale(modelMat, phys.meshScale);
    
    shad->setMat4("model", modelMat);
}


void Object::SetupPhysic(PhysicsWorld* physworld, PhysicsCommon* physicsCommon) {
    this->phys.world = physworld;
    this->phys.physicsCommon = physicsCommon;
    phys.physicsEnable = true;
}

void Object::CreateRigidBody(){
    Vector3 position(phys.meshPosition.x, phys.meshPosition.y, phys.meshPosition.z);
    Quaternion orientation = Quaternion::fromEulerAngles(glm::radians(phys.angleRotate.x), glm::radians(phys.angleRotate.y), glm::radians(phys.angleRotate.z));
    Transform transform(position, orientation);
    phys.body = phys.world->createRigidBody(transform);
    phys.body->setType(BodyType::KINEMATIC);
}

void Object::RotateMesh(float anglex, float angley, float anglez) {
    phys.angleRotate.x += anglex;
    phys.angleRotate.y += angley;
    phys.angleRotate.z += anglez;
    if (phys.physicsEnable) {
        Transform currentTransform = phys.body->getTransform();
        Quaternion orientation = currentTransform.getOrientation();
        orientation = Quaternion::fromEulerAngles(phys.angleRotate.x, phys.angleRotate.y, phys.angleRotate.z);
        currentTransform.setOrientation(orientation);
        phys.body->setTransform(currentTransform);
    }
}

void Object::SetRotateMesh(float anglex, float angley, float anglez) {
        phys.angleRotate.x = anglex;
        phys.angleRotate.y = angley;
        phys.angleRotate.z = anglez;
        if (phys.physicsEnable) {
            Transform currentTransform = phys.body->getTransform();
            Quaternion orientation = currentTransform.getOrientation();
            orientation = Quaternion::fromEulerAngles(phys.angleRotate.x, phys.angleRotate.y, phys.angleRotate.z);
            //std::cout << angleRotate.x << " " << angleRotate.y << " " << angleRotate.z << " " << orientation.getVectorV().x << " " << orientation.getVectorV().y << " " << orientation.getVectorV().z << std::endl;
            currentTransform.setOrientation(orientation);
            phys.body->setTransform(currentTransform);
        }
    }

void Object::MoveObject(glm::vec3 position) {
    phys.meshPosition += position;
    if (phys.physicsEnable) {
        Transform currentTransform = phys.body->getTransform();
        Vector3 pos;
        pos.setAllValues(phys.meshPosition.x, phys.meshPosition.y, phys.meshPosition.z);
        currentTransform.setPosition(pos);
        phys.body->setTransform(currentTransform);
    }
}

void Object::SetObjectPosition(glm::vec3 position) {
        phys.meshPosition = glm::vec3(0.0f);
        MoveObject(position);
    }

void Object::Draw(Shader& shader){
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

void Object::setupMesh(){

    std::cout << "Mesh Setup \n";
   const size_t vertsSz = sizeof(glm::vec3) * verticles.size();
  const size_t normSz = sizeof(glm::vec3) * normal.size();
  const size_t texcoordSz = sizeof(glm::vec2) * textCoord.size();
  
  glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertsSz + normSz + texcoordSz, NULL, GL_STATIC_DRAW);
  
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertsSz, &verticles[0]);
    glBufferSubData(GL_ARRAY_BUFFER, vertsSz, normSz, &normal[0]);
    glBufferSubData(GL_ARRAY_BUFFER, vertsSz + normSz, texcoordSz, &textCoord[0]);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
        &indices[0], GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertsSz, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, normSz, (void*)(vertsSz));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, texcoordSz, (void*)(vertsSz + normSz)); 
    

    glBindVertexArray(0);
    }