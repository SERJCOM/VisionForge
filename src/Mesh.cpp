#include "mesh.hpp"



Mesh::Mesh(std::vector<Vertex> vertices , std::vector<unsigned int> indices, std::vector<sTexture> textures){
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    //SetupMesh();
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
        glDrawArrays(GL_TRIANGLES, 0, indices.size() * 3);
        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);
}





