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

struct texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh{
protected:
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<texture> textures;

    unsigned int VAO, VBO, EBO;

    // virtual void SetupMesh();

public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<texture> textures);

    virtual void Draw(Shader& shader);

    
};