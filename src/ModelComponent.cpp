#include "VisionForge/EntitySystem/DefaulComponents/ModelComponent.hpp"
#include "VisionForge/Common/Timer.hpp"

using namespace vision;

ModelComponent::ModelComponent(std::string path)
{
    SetPath(path);
}

ModelComponent::ModelComponent(const char *path)
{
    SetPath(path);
}

void ModelComponent::Draw()
{
    glm::mat4 modelMat = glm::mat4(1);
    modelMat = glm::scale(modelMat, GetObjectSize());

    gEngine->GetSystemPtr()->GetCurrentShader()->setMat4("model", modelMat);

    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        meshes[i].Draw(*gEngine->GetSystemPtr()->GetCurrentShader());
    }
}

void ModelComponent::LoadModel()
{
    LoadModel(path);
}

void ModelComponent::AddMaterial(Material *mat)
{
    _material = mat;
}

void ModelComponent::SetPath(std::filesystem::path path)
{
    this->path = path.c_str();
}


// PRIVATE

void ModelComponent::LoadModel(std::string path)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_GenBoundingBoxes | aiProcess_CalcTangentSpace | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);

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

void ModelComponent::processNode(aiNode *node, const aiScene *scene, int index)
{
    int ind = index;
    ind++;

    for (size_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
        // std::cout << mesh->mName.C_Str() << std::endl;
        meshNames[node->mName.C_Str()] = static_cast<int>(meshes.size()) - 1;
    }

    for (size_t i = 0; i < node->mNumChildren; i++)
        processNode(node->mChildren[i], scene, ind);
}

Mesh ModelComponent::processMesh(aiMesh *mesh, const aiScene *scene)
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
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    std::cout << "texture name: " << material->GetName().C_Str() << std::endl;
    
    std::cout << "mesh name: " << mesh->mName.C_Str() << std::endl;
    if (_material != nullptr)
    {
        std::vector<sTexture> materials = _material->GetTexture(material->GetName().C_Str(), textures_loaded);
        textures.insert(textures.end(), materials.begin(), materials.end());
    }
    else
    {
        std::vector<sTexture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    }

    return Mesh(vertices, indices, textures);
}

std::vector<sTexture> ModelComponent::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
    std::vector<sTexture> textures;

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);

        std::cout << "texture: " << mat->GetName().C_Str() << " " << std::endl;

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