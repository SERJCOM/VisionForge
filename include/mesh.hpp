#pragma once
#include <iostream>
#include <vector>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec2 TexCoords;
    glm::vec3 Normal;
};

struct sTexture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh{
protected:

    

    unsigned int VAO, VBO, EBO;

    // virtual void SetupMesh();

public:

    std::vector<Vertex>       vertices;    
    std::vector<unsigned int> indices;
    std::vector<sTexture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<sTexture> textures);

    Mesh();

    

    virtual void Draw(Shader& shader);

    std::vector<Vertex> GetVertices(){
        return vertices;
    }

    std::vector<unsigned int> GetIndices(){
        return indices;
    }

    std::vector<sTexture> GetTexture(){
        return textures;
    }
    
};