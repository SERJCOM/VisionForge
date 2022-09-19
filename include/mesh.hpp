#pragma once
#include <iostream>
#include <vector>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

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
    std::vector<texture> textures;

    unsigned int VAO, VBO, EBO;

    // virtual void SetupMesh();

public:
    Mesh(std::vector<glm::vec3> vert, std::vector<glm::vec3> normal, std::vector<glm::vec2> textCoord, std::vector<unsigned int> indices, std::vector<texture> textures);

    virtual void Draw(Shader& shader);

    
};