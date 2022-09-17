#include "mesh.hpp"

Mesh::Mesh( std::vector<glm::vec3> vert, std::vector<glm::vec3> normal, std::vector<glm::vec2> textCoord, std::vector<unsigned int> indices, std::vector<texture> textures){
    this->verticles = vert;
    this->normal = normal;
    this->textCoord = textCoord;
    this->indices = indices;
    this->textures = textures;

    SetupMesh();
}


void Mesh::SetupMesh(){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verticles), &verticles);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(verticles), sizeof(normal), &normal);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(verticles) + sizeof(normal), sizeof(textCoord), &textCoord);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);  
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(sizeof(verticles)));  
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(sizeof(verticles) + sizeof(normal))); 

    glBindVertexArray(0);
}

void Mesh::Draw(Shader& shader){
    glActiveTexture(GL_TEXTURE0);

        unsigned int diffuseNr = 1;
        for (unsigned int i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); 
            std::string number;
            std::string name = textures[i].type;
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            
            glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, verticles.size() * 3);
        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);
}





