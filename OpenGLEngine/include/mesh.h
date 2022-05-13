#pragma once

#include "init.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;

struct Vertex {
    glm::vec3 Position;
    glm::vec2 TexCoords;

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

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<texture> textures){
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;
        
        setupMesh();
    }
    void Draw(Shader shader) {     
        glActiveTexture(GL_TEXTURE0);

        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        unsigned int heightNr = 1;
        for (unsigned int i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); // перед св€зыванием активируем нужный текстурный юнит

            // ѕолучаем номер текстуры (номер N в diffuse_textureN)
            string number;
            string name = textures[i].type;
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++); // конвертируем unsigned int в строку
            else if (name == "texture_normal")
                number = std::to_string(normalNr++); // конвертируем unsigned int в строку
            else if (name == "texture_height")
                number = std::to_string(heightNr++); // конвертируем unsigned int в строку

           
            // “еперь устанавливаем сэмплер на нужный текстурный юнит
            glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
            // и св€зываем текстуру
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }

        
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);
    }
private:
    unsigned int VAO, VBO, EBO;

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

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
        

        glBindVertexArray(0);
    }
};




class Model
{
public: 
    std::vector<Mesh> meshes;
    std::string directory;
    vector<texture> textures_loaded;
    bool gammaCorrection;
    Model(std::string path)
    {
        loadModel(path);
    }
    void Draw(Shader& shader)
    {
        for (unsigned int i = 0; i < meshes.size(); i++)
            meshes[i].Draw(shader);
    }
private:
    void loadModel(std::string path)
    {
        Assimp::Importer import;
        const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
            return;
        }
        directory = path.substr(0, path.find_last_of('/'));

        processNode(scene->mRootNode, scene);
    }

    void processNode(aiNode* node, const aiScene* scene)
    {
        std::cout << node->mNumChildren << std::endl;
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(mesh, scene));
        }
       
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }
    }

    Mesh processMesh(aiMesh* mesh, const aiScene* scene)
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

            if (mesh->mTextureCoords[0]) // если меш содержит текстурные координаты
            {
                glm::vec2 vec;

                // ¬ершина может содержать до 8 различных текстурных координат. ћы предполагаем, что мы не будем использовать модели,
                // в которых вершина может содержать несколько текстурных координат, поэтому мы всегда берем первый набор (0)
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoords = vec;
            }
            else {
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);
            }

            vertices.push_back(vertex);

            

        }

       

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }
        
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
       

        vector<texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
       
        

        // ¬озвращаем Mesh-объект, созданный на основе полученных данных
        return Mesh(vertices, indices, textures);
    }

    vector<texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
    {
        vector<texture> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);

            // ѕровер€ем, не была ли текстура загружена ранее, и если - да, то пропускаем загрузку новой текстуры и переходим к следующей итерации
            bool skip = false;
            for (unsigned int j = 0; j < textures_loaded.size(); j++)
            {
                if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
                {
                    textures.push_back(textures_loaded[j]);
                    skip = true; // текстура с тем же путем к файлу уже загружена, переходим к следующей (оптимизаци€)
                    break;
                }
            }
            if (!skip)
            {   // если текстура еще не была загружена, то загружаем еЄ
                texture texturee;
                texturee.id = LoadTextureFromFile(str.C_Str(), this->directory);
                texturee.type = typeName;
                texturee.path = str.C_Str();
                textures.push_back(texturee);
                textures_loaded.push_back(texturee); // сохран€ем текстуру в массиве с уже загруженными текстурами, тем самым гарантиру€, что у нас не по€в€тс€ без необходимости дубликаты текстур
            }
        }
        return textures;
    }
    
    
};