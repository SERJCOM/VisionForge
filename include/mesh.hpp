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
    

    std::vector<glm::vec3> vert;

    int width, height;

    float quadVertices[26];

    // virtual void SetupMesh();

public:
    unsigned int VAO, VBO, EBO;

    std::vector<Vertex>       vertices;    
    std::vector<unsigned int> indices;
    std::vector<sTexture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<sTexture> textures);

    Mesh(std::vector<glm::vec3> vertices);

    Mesh(){}

    void Create2DRectangle();

    void DrawRectangle(Shader& shad, int texture);

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