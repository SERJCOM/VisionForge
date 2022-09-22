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
    for (unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Draw(shader);
}

void Model::ScaleMesh(std::string name, glm::vec3 size) {
    if (meshNames.find(name) == meshNames.end())    std::cout << "the element was not found\n";
    else    meshes[meshNames[name]].ScaleMesh(size);
}

void Model::ScaleObject(glm::vec3 size) {
    objectScale = size;
    for (int i = 0; i < meshes.size(); i++) {
        meshes[i].ScaleMesh(size);
    }
}

void Model::RotateMesh(std::string name, float anglex, float angley, float anglez) {
    meshes[meshNames[name]].RotateMesh(anglex, angley, anglez);
}

void Model::RotateObject(float anglex, float angley, float anglez) {
    objectAngleRotate += glm::vec3(glm::radians(anglex), glm::radians(angley), glm::radians(anglez));
    Quaternion orientation = Quaternion::fromEulerAngles(objectAngleRotate.x, objectAngleRotate.y, objectAngleRotate.z);
    Transform transform;
    transform.setOrientation(orientation);
    body->setTransform(transform);
}

void Model::RotateObject(glm::vec3 angles) {
    objectAngleRotate += glm::radians(angles);
    Quaternion orientation = Quaternion::fromEulerAngles(objectAngleRotate.x, objectAngleRotate.y, objectAngleRotate.z);
    Transform transform = body->getTransform();
    transform.setOrientation(orientation);
    body->setTransform(transform);
}

void Model::SetMeshRotation(std::string name, float anglex, float angley, float anglez) {
    meshes[meshNames[name]].SetMeshRotation(anglex, angley, anglez);
}

void Model::SetObjectRotation(float anglex, float angley, float anglez) {
    objectAngleRotate = glm::vec3(anglex, angley, anglez);

    Transform transform = body->getTransform();
    transform.setOrientation(Quaternion::fromEulerAngles(objectAngleRotate.x, objectAngleRotate.y, objectAngleRotate.z));
    body->setTransform(transform);
}

void Model::SetObjectRotation(glm::vec3 rot) {
    objectAngleRotate = glm::radians(rot);

    Transform transform = body->getTransform();
    transform.setOrientation(Quaternion::fromEulerAngles(objectAngleRotate.x, objectAngleRotate.y, objectAngleRotate.z));
    body->setTransform(transform);
}

void Model::MoveObject(float x, float y, float z) {
    
    Vector3 pos = body->getTransform().getPosition();
    Transform transform = body->getTransform();
    pos = Vector3(pos.x + x, pos.y + y, pos.z + z);
    transform.setPosition(pos);
    body->setTransform(transform);

}

void Model::MoveMesh(std::string name, float x, float y, float z) {
    if (meshNames.find(name) == meshNames.end())    std::cout << "the element was not found\n";
    else    meshes[meshNames[name]].MoveObject(glm::vec3(x, y, z));
}

void Model::SetMeshPosition(std::string name, float x, float y, float z) {
    if (meshNames.find(name) == meshNames.end())    std::cout << "the element was not found\n";
    else    meshes[meshNames[name]].SetObjectPosition(glm::vec3(x, y, z));
}

void Model::SetObjectPosition(float x, float y, float z) {
    Transform transform = body->getTransform();
    transform.setPosition(Vector3(x, y, z));
    body->setTransform(transform);
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
     const size_t sizeVertices = meshes[0].vertices.size();
    const size_t sizeTriangles = meshes[0].indices.size();

    triangleArray = new TriangleVertexArray(
        sizeVertices, &meshes[0].vertices[0].Position, sizeof(meshes[0].vertices), 
    &meshes[0].vertices[0].Normal.x, sizeof(meshes[0].vertices),   
    sizeTriangles / 3, &meshes[0].indices[0], 3 * sizeof(unsigned int),
    rp3d::TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
	rp3d::TriangleVertexArray::NormalDataType::NORMAL_FLOAT_TYPE,
	rp3d::TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE
    );

    size_object = Vector3(10, 10, 10);
    triangleMesh = physicsCommon->createTriangleMesh();
    triangleMesh->addSubpart(triangleArray);
    concaveMesh = physicsCommon->createConcaveMeshShape(triangleMesh, Vector3(1.0f, 1.0f, 1.0f)) ;
    body->addCollider(concaveMesh, body->getTransform());
}

void Model::SetTypeOfThePhysObject(bool flag) {
    if (flag) {
        body->setType(BodyType::KINEMATIC);
    }
    else {
        //body->setType(BodyType::DYNAMIC);
    }
}

void Model::PrintObjectPosition() {
    Transform trans = body->getTransform();
    Vector3 pos = trans.getPosition();
    std::cout << pos.to_string() << std::endl;
}

void Model::UpdateObjectTransform() {
    Transform transform = body->getTransform();
    glm::vec3 position = glm::vec3(transform.getPosition().x, transform.getPosition().y, transform.getPosition().z);
    Quaternion orientation = transform.getOrientation();
    decimal angle;
    Vector3 axis;
    orientation.getRotationAngleAxis(angle, axis);
    glm::quat quatPosition = glm::angleAxis(angle, glm::vec3(axis.x, axis.y, axis.z));
    glm::vec3 vecangles = glm::eulerAngles(quatPosition);
    for (int i = 0; i < meshes.size(); i++) {
        meshes[i].SetObjectPosition(position);
        meshes[i].SetMeshRotation(vecangles.x , vecangles.y, vecangles.z);
    }
}

// PRIVATE

void Model::loadModel(std::string path)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_GenBoundingBoxes | aiProcess_CalcTangentSpace | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    rootName = scene->mRootNode->mName.C_Str();
    std::cout << "the root name is " << rootName << std::endl;
    processNode(scene->mRootNode, scene, number);
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