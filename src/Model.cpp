#include "VisionForge/EntitySystem/DefaulComponents/ModelComponent.hpp"
#include "VisionForge/Common/Timer.hpp"

using namespace lthm;

ModelComponent::ModelComponent(std::string path) {
    SetPath(path);
}

ModelComponent::ModelComponent(const char* path)
{
    SetPath(path);
}

void ModelComponent::Draw(Shader& shader)
{
    glm::mat4 modelMat = glm::mat4(1);
    modelMat = glm::scale(modelMat, objectScale);
    
    shader_->use();
    shader.setMat4("model", modelMat);

    for (unsigned int i = 0; i < meshes.size(); i++){
        meshes[i].Draw(shader);
    }
}

void ModelComponent::LoadModel()
{
    LoadModel(path);
}

void ModelComponent::AddMaterial(Li::Material* mat)
{
    _material = mat;
}

void ModelComponent::SetPath(std::string path)
{
    this->path = path;
}

// void ModelComponent::ScaleMesh(std::string name, glm::vec3 size) {
//     if (meshNames.find(name) == meshNames.end())    std::cout << "the element was not found\n";
//     else   { 
//         if(MeshParameters.find(name) == MeshParameters.end()){
//             sMeshParameters mm;
//             MeshParameters.insert(make_pair(name, mm));
//         }
//         meshes[meshNames[name]].ScaleMesh(size);
//     }
// }

void ModelComponent::ScaleObject(glm::vec3 size) {
    objectScale = size;
}

// void ModelComponent::RotateMesh(std::string name, float anglex, float angley, float anglez) {
//     meshes[meshNames[name]].RotateMesh(anglex, angley, anglez);
// }

void ModelComponent::RotateObject(float anglex, float angley, float anglez) {
    objectAngleRotate += glm::vec3(glm::radians(anglex), glm::radians(angley), glm::radians(anglez));

    // if(body != nullptr){
    //     Quaternion orientation = Quaternion::fromEulerAngles(objectAngleRotate.x, objectAngleRotate.y, objectAngleRotate.z);
    //     Transform transform;
    //     transform.setOrientation(orientation);
    //     body->setTransform(transform);
    // }
}

void ModelComponent::RotateObject(glm::vec3 angles) {
    objectAngleRotate += glm::radians(angles);

    // if(body != nullptr){
    //     Quaternion orientation = Quaternion::fromEulerAngles(objectAngleRotate.x, objectAngleRotate.y, objectAngleRotate.z);
    //     Transform transform = body->getTransform();
    //     transform.setOrientation(orientation);
    //     body->setTransform(transform);
    // }
}

// void ModelComponent::SetMeshRotation(std::string name, float anglex, float angley, float anglez) {
//     meshes[meshNames[name]].SetMeshRotation(anglex, angley, anglez);
// }

void ModelComponent::SetObjectRotation(float anglex, float angley, float anglez) {
    objectAngleRotate = glm::radians(glm::vec3(anglex, angley, anglez));

    // if(body != nullptr){    
    //     Transform transform = body->getTransform();
    //     transform.setOrientation(Quaternion::fromEulerAngles(objectAngleRotate.x, objectAngleRotate.y, objectAngleRotate.z));
    //     body->setTransform(transform);
    // }
}

void ModelComponent::SetObjectRotation(glm::vec3 rot) {
    objectAngleRotate = glm::radians(rot);
    // if(body != nullptr){
    //     Transform transform = body->getTransform();
    //     transform.setOrientation(Quaternion::fromEulerAngles(objectAngleRotate.x, objectAngleRotate.y, objectAngleRotate.z));
    //     body->setTransform(transform);
    // }
}

void ModelComponent::MoveObject(float x, float y, float z) {
    objectPosition = glm::vec3(x, y, z);
    // if(body != nullptr){
    //     Vector3 pos = body->getTransform().getPosition();
    //     Transform transform = body->getTransform();
    //     pos = Vector3(pos.x + x, pos.y + y, pos.z + z);
    //     transform.setPosition(pos);
    //     body->setTransform(transform);
    // }

}





// PRIVATE

void ModelComponent::LoadModel(std::string path)
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

void ModelComponent::processNode(aiNode* node, const aiScene* scene, int index)
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

Object ModelComponent::processMesh(aiMesh* mesh, const aiScene* scene)
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
    std::cout << "texture name: " << material->GetName().C_Str() <<  std::endl;
    std::cout << "mesh name: " << mesh->mName.C_Str() << std::endl;
    if(_material != nullptr){
        std::vector<sTexture> materials = _material->GetTexture(material->GetName().C_Str(), textures_loaded);
        textures.insert(textures.end(), materials.begin(), materials.end());
    }
    else{
        std::vector<sTexture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    }

    return Object(vertices, indices, textures);
}

std::vector<sTexture> ModelComponent::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    std::vector<sTexture> textures;

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);

        std::cout << "texture: " << mat->GetName().C_Str() << " "   << std::endl;

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