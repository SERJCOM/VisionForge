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
    std::vector<glm::vec3> verticles;
    std::vector<glm::vec3> normal;
    std::vector<unsigned int> indices;
    std::vector<glm::vec2> textCoord;

    unsigned int VAO, VBO, EBO;

    void SetupMesh();


public:
    Mesh(Vertex vert, std::vector<unsigned int> indices, std::vector<texture> textures);

    virtual void Draw(Shader shader);
    
};