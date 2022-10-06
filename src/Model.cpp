#include "model.h"

Model::Model(std::string path, PhysicsWorld* physworld, PhysicsCommon* physicsCommon) {
    this->physworld = physworld;
    this->physicsCommon = physicsCommon;
    loadModel(path);
}

Model::Model(const char* path, PhysicsWorld* physworld, PhysicsCommon* physicsCommon)
{
    this->physworld = physworld;
    this->physicsCommon = physicsCommon;
    loadModel(path);
}

void Model::Draw(Shader& shader)
{
    glm::vec3 vecangles;
    glm::vec3 position;
    if(body != nullptr){
        Transform transform = body->getTransform();
        position = glm::vec3(transform.getPosition().x, transform.getPosition().y, transform.getPosition().z);
        Quaternion orientation = transform.getOrientation();
        decimal angle;
        Vector3 axis;
        orientation.getRotationAngleAxis(angle, axis);
        vecangles = glm::eulerAngles(glm::angleAxis(angle, glm::vec3(axis.x, axis.y, axis.z)));
    }
    else{
        position = objectPosition;
        vecangles = objectAngleRotate;
    }
    
    //  setMatrix

    Quaternion orientation;
    Vector3 positionVec;
    orientation = Quaternion::fromEulerAngles(vecangles.x, vecangles.y, vecangles.z);
    positionVec = Vector3(position.x, position.y, position.z);
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
    glm::mat4 modelMat = glm::mat4(1);
    modelMat = glm::translate(modelMat, glm::vec3(position.x, position.y, position.z));
    modelMat = modelMat * orientMat;
    modelMat = glm::scale(modelMat, objectScale);
    
    shader.setMat4("model", modelMat);

    for (unsigned int i = 0; i < meshes.size(); i++){
        meshes[i].Draw(shader);
    }
}

// void Model::ScaleMesh(std::string name, glm::vec3 size) {
//     if (meshNames.find(name) == meshNames.end())    std::cout << "the element was not found\n";
//     else   { 
//         if(MeshParameters.find(name) == MeshParameters.end()){
//             sMeshParameters mm;
//             MeshParameters.insert(make_pair(name, mm));
//         }
//         meshes[meshNames[name]].ScaleMesh(size);
//     }
// }

void Model::ScaleObject(glm::vec3 size) {
    objectScale = size;
}

// void Model::RotateMesh(std::string name, float anglex, float angley, float anglez) {
//     meshes[meshNames[name]].RotateMesh(anglex, angley, anglez);
// }

void Model::RotateObject(float anglex, float angley, float anglez) {
    objectAngleRotate += glm::vec3(glm::radians(anglex), glm::radians(angley), glm::radians(anglez));

    if(body != nullptr){
        Quaternion orientation = Quaternion::fromEulerAngles(objectAngleRotate.x, objectAngleRotate.y, objectAngleRotate.z);
        Transform transform;
        transform.setOrientation(orientation);
        body->setTransform(transform);
    }
}

void Model::RotateObject(glm::vec3 angles) {
    objectAngleRotate += glm::radians(angles);

    if(body != nullptr){
        Quaternion orientation = Quaternion::fromEulerAngles(objectAngleRotate.x, objectAngleRotate.y, objectAngleRotate.z);
        Transform transform = body->getTransform();
        transform.setOrientation(orientation);
        body->setTransform(transform);
    }
}

// void Model::SetMeshRotation(std::string name, float anglex, float angley, float anglez) {
//     meshes[meshNames[name]].SetMeshRotation(anglex, angley, anglez);
// }

void Model::SetObjectRotation(float anglex, float angley, float anglez) {
    objectAngleRotate = glm::radians(glm::vec3(anglex, angley, anglez));

    if(body != nullptr){    
        Transform transform = body->getTransform();
        transform.setOrientation(Quaternion::fromEulerAngles(objectAngleRotate.x, objectAngleRotate.y, objectAngleRotate.z));
        body->setTransform(transform);
    }
}

void Model::SetObjectRotation(glm::vec3 rot) {
    objectAngleRotate = glm::radians(rot);
    if(body != nullptr){
        Transform transform = body->getTransform();
        transform.setOrientation(Quaternion::fromEulerAngles(objectAngleRotate.x, objectAngleRotate.y, objectAngleRotate.z));
        body->setTransform(transform);
    }
}

void Model::MoveObject(float x, float y, float z) {
    objectPosition += glm::vec3(x, y, z);
    if(body != nullptr){
        Vector3 pos = body->getTransform().getPosition();
        Transform transform = body->getTransform();
        pos = Vector3(pos.x + x, pos.y + y, pos.z + z);
        transform.setPosition(pos);
        body->setTransform(transform);
    }

}

// void Model::MoveMesh(std::string name, float x, float y, float z) {
//     if (meshNames.find(name) == meshNames.end())    std::cout << "the element was not found\n";
//     else    meshes[meshNames[name]].MoveObject(glm::vec3(x, y, z));
// }

// void Model::SetMeshPosition(std::string name, float x, float y, float z) {
//     if (meshNames.find(name) == meshNames.end())    std::cout << "the element was not found\n";
//     else    meshes[meshNames[name]].SetObjectPosition(glm::vec3(x, y, z));
// }

void Model::SetObjectPosition(float x, float y, float z) {
    objectPosition = glm::vec3(x,y,z);
    if(body != nullptr){
        Transform transform = body->getTransform();
        transform.setPosition(Vector3(objectPosition.x, objectPosition.y, objectPosition.z));
        body->setTransform(transform);
    }
}

void Model::SetupPhysicMeshByName(std::string name) {
    meshes[meshNames[name]].SetupPhysic(physworld, physicsCommon);
    meshes[meshNames[name]].CreateRigidBody();
}

void Model::CreatePhysicsBody() {
    Vector3 position(objectPosition.x, objectPosition.y, objectPosition.z);
    Quaternion orientation = Quaternion::fromEulerAngles(glm::radians(objectAngleRotate.x), glm::radians(objectAngleRotate.y), glm::radians(objectAngleRotate.z));
    Transform transform(position, orientation);
    body = physworld->createRigidBody(transform);
}


void Model::CreateCollisionBox(glm::vec3 halfsize) {
    const Vector3 halfExtents(halfsize.x, halfsize.y, halfsize.z);
    BoxShape* boxShape = physicsCommon->createBoxShape(halfExtents);
    Collider* collider;
    collider = body->addCollider(boxShape, body->getTransform());
}

void Model::CreateCollisionSphere(float radius) {
    SphereShape* sphereShape = physicsCommon->createSphereShape(radius);
    body->addCollider(sphereShape, body->getTransform());
}

void Model::CreateCollisionCapsule(glm::vec2 halfSize) {
    CapsuleShape* capsuleShape = physicsCommon->createCapsuleShape(halfSize.x, halfSize.y);
    body->addCollider(capsuleShape, body->getTransform());
}

void Model::CreateConcaveMeshShape(){
    
    for(int i = 0; i < meshes.size(); i++){
        sConcaveMesh conc;
        concavemesh.push_back(conc);

        const size_t meshesSize = meshes.size();
        const size_t sizeVertices = meshes[i].vertices.size();
        const size_t sizeTriangles = meshes[i].indices.size();

        concavemesh.back().triangleArray = new TriangleVertexArray(
            sizeVertices, &meshes[i].vertices[0].Position, sizeof(meshes[i].vertices), 
        &meshes[i].vertices[0].Normal.x, sizeof(meshes[i].vertices),   
        sizeTriangles / 3, &meshes[i].indices[0], 3 * sizeof(unsigned int),
        rp3d::TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
        rp3d::TriangleVertexArray::NormalDataType::NORMAL_FLOAT_TYPE,
        rp3d::TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE
        );

        concavemesh.back().triangleMesh = physicsCommon->createTriangleMesh();
         concavemesh.back().triangleMesh->addSubpart(concavemesh.back().triangleArray);
        concavemesh.back().concaveMesh = physicsCommon->createConcaveMeshShape(concavemesh.back().triangleMesh, Vector3(objectScale.x, objectScale.y, objectScale.z)) ;
        body->addCollider(concavemesh.back().concaveMesh, body->getTransform());
    }
}

void Model::SetTypeOfThePhysObject(bool flag) {
    if (flag) {
        body->setType(BodyType::KINEMATIC);
    }
    else {
        body->setType(BodyType::DYNAMIC);
    }
}

void Model::PrintObjectPosition() {
    Transform trans = body->getTransform();
    Vector3 pos = trans.getPosition();
    std::cout << pos.to_string() << std::endl;
}


// PRIVATE

void Model::loadModel(std::string path)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_GenBoundingBoxes | aiProcess_CalcTangentSpace | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    rootName = scene->mRootNode->mName.C_Str();
    std::cout << "the root name is " << rootName << std::endl;
    
    processNode(scene->mRootNode, scene, number);

    std::cout << " count of the meshes is " << meshes.size() << std::endl;
}

void Model::processNode(aiNode* node, const aiScene* scene, int index)
{
    int ind = index;
    ind++;


    for (size_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
        //std::cout << mesh->mName.C_Str() << std::endl;
        meshNames[node->mName.C_Str()] = static_cast<int>(meshes.size()) - 1;
    }


    for (size_t i = 0; i < node->mNumChildren; i++)   processNode(node->mChildren[i], scene, ind);

}

Object Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<sTexture> textures;

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
        else vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)     indices.push_back(face.mIndices[j]);
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<sTexture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    // if(Vector3(mesh->mAABB.mMin.x, mesh->mAABB.mMin.y, mesh->mAABB.mMin.z).length() < modelBoundingBox){

    // }

    return Object(vertices, indices, textures);
}

std::vector<sTexture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    std::vector<sTexture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);

        //std::cout << "texture: " << mat->GetName().C_Str() << std::endl;

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
            sTexture texturee;
            texturee.id = Texture::LoadTextureFromFile(str.C_Str(), this->directory);
            texturee.type = typeName;
            texturee.path = str.C_Str();
            textures.push_back(texturee);
            textures_loaded.push_back(texturee);
        }
    }
    return textures;
}