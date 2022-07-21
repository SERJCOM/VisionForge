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
    else    meshes[meshNames[name]].meshScale = size;
}

void Model::ScaleObject(glm::vec3 size) {
    objectScale = size;
    for (int i = 0; i < meshes.size(); i++) {
        meshes[i].meshScale = size;
    }
}

void Model::RotateMesh(std::string name, float anglex, float angley, float anglez) {
    meshes[meshNames[name]].RotateMesh(anglex, angley, anglez);
}

void Model::RotateObject(float anglex, float angley, float anglez) {
    objectAngleRotate += glm::vec3(anglex, angley, anglez);
    Quaternion orientation = Quaternion::fromEulerAngles(objectAngleRotate.x, objectAngleRotate.y, objectAngleRotate.z);
    Transform transform;
    transform.setOrientation(orientation);
    body->setTransform(transform);

    for (int i = 0; i < meshes.size(); i++) {
        meshes[i].RotateMesh(anglex, angley, anglez);
    }
}

void Model::RotateObject(glm::vec3 angles) {
    objectAngleRotate += angles;
    Quaternion orientation = Quaternion::fromEulerAngles(objectAngleRotate.x, objectAngleRotate.y, objectAngleRotate.z);
    Transform transform;
    transform.setOrientation(orientation);
    body->setTransform(transform);
    for (int i = 0; i < meshes.size(); i++) {
        meshes[i].RotateMesh(angles.x, angles.y, angles.z);
    }
}

void Model::SetMeshRotation(std::string name, float anglex, float angley, float anglez) {
    meshes[meshNames[name]].SetRotateMesh(anglex, angley, anglez);
}

void Model::SetObjectRotation(float anglex, float angley, float anglez) {
    objectAngleRotate = glm::vec3(anglex, angley, anglez);
    Quaternion orientation = Quaternion::fromEulerAngles(anglex, angley, anglez);
    Transform transform;
    transform.setOrientation(orientation);
    body->setTransform(transform);

    for (int i = 0; i < meshes.size(); i++) {
        meshes[i].RotateMesh(anglex, angley, anglez);
    }
}

void Model::MoveObject(float x, float y, float z) {
    objectPosition += glm::vec3(x, y, z);
    Transform transform;
    transform.setPosition(Vector3(objectPosition.x, objectPosition.y, objectPosition.z));
    body->setTransform(transform);

    for (int i = 0; i < meshes.size(); i++) {
        meshes[i].MoveObject(glm::vec3(x, y, z));
    }
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
    objectPosition = glm::vec3(x, y, z);
    Transform transform;
    transform.setPosition(Vector3(x, y, z));
    body->setTransform(transform);

    for (int i = 0; i < meshes.size(); i++)
        meshes[i].SetObjectPosition(glm::vec3(x, y, z));
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
    body->setType(BodyType::KINEMATIC);
}

void Model::loadModel(std::string path)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

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


    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
        //std::cout << mesh->mName.C_Str() << std::endl;
        meshNames[node->mName.C_Str()] = meshes.size() - 1;
    }


    for (unsigned int i = 0; i < node->mNumChildren; i++)   processNode(node->mChildren[i], scene, ind);

}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<texture> textures;

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
    std::vector<texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    return Mesh(vertices, indices, textures);
}

std::vector<texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    std::vector<texture> textures;
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
            texture texturee;
            texturee.id = Texture::LoadTextureFromFile(str.C_Str(), this->directory);
            texturee.type = typeName;
            texturee.path = str.C_Str();
            textures.push_back(texturee);
            textures_loaded.push_back(texturee);
        }
    }
    return textures;
}