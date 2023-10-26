#pragma once
#include <iostream>
#include <vector>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/mesh.h>

#include "VisionForge/System/Shader.hpp"
#include "VisionForge/EntitySystem/Component.hpp"
#include "VisionForge/Engine/Object.hpp"

namespace vision
{

    struct Vertex
    {
        glm::vec3 Position;
        glm::vec2 TexCoords;
        glm::vec3 Normal;
    };

    struct sTexture
    {
        unsigned int id;
        std::string type;
        std::string path;
    };

    class Mesh : public Object
    {
    public:
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<sTexture> textures);

        void Draw(Shader &shader);

        virtual ~Mesh();

    private:
        unsigned int VAO, VBO, EBO;

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<sTexture> textures;

        glm::mat4 modelMat;

        void SetMatrix(Shader *shad);

        void setupMesh();
    };

}