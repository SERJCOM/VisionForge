#include "VisionForge/Engine/Mesh.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace vision;

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<sTexture> textures)
{
    this->vertices = std::move(vertices);
    this->indices = std::move(indices);
    this->textures = std::move(textures);
    this->setupMesh();
}

Mesh::~Mesh()
{
    // delete phys;
}

void Mesh::Draw(Shader &shader)
{

    SetMatrix(shader);

    glActiveTexture(GL_TEXTURE0);

    unsigned int diffuseNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string number;
        std::string name = textures[i].type;
        std::string sBool = "bool_" + name;
        glUniform1i(glGetUniformLocation(shader.ID, (name).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);

        glUniform1i(glGetUniformLocation(shader.ID, sBool.c_str()), 1);
    }

    shader.BindSSBO();

    glBindVertexArray(VAO);
    glDrawElementsInstanced(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0, 1);

    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::SetMatrix(Shader &shad)
{

    glm::mat4 modelMat = glm::mat4(1);

    

    modelMat = glm::translate(modelMat, GetObjectPosition());

    modelMat = glm::rotate(modelMat, angle_, rotate_);

    modelMat = glm::scale(modelMat, GetObjectSize());

    shad.setMat4("model", modelMat);
}

void Mesh::setupMesh()
{
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}