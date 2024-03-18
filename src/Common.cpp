#include "VisionForge/Common/Common.hpp"
#include <GL/glew.h>



namespace vision{
std::ostream& operator << (std::ostream& out, glm::vec3 vec){
    out << "x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z;
    return out;
}

unsigned int quadVAO = 0;
unsigned int quadVBO;

void RenderQuad(){
    if (quadVAO == 0)
    {
        float quadVertices[] = {
             // координаты      // текстурные коодинаты
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
		
        // Установка VAO плоскости
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

std::filesystem::path GetGameSdkPath()
{
    // return std::filesystem::current_path();

     #ifdef GAMESDK_DIRECTORY
        std::cout << "GAMESDK_DIRECTORY :" << GAMESDK_DIRECTORY << std::endl;
        return GAMESDK_DIRECTORY;
    #else 
        throw std::exception("GAMESDK_DIRECTORY is not enabled");
    #endif
}

std::filesystem::path GetCurrentPath()
{
    // auto curpath = std::filesystem::current_path() / std::filesystem::path("..");
    // curpath.lexically_normal();
    #ifdef CURRENT_DIRECTORY
        std::cout << "CURRENT_DIRECTORY :" << CURRENT_DIRECTORY << std::endl;
        return CURRENT_DIRECTORY;
    #else 
        throw std::exception("CURRENT_DIRECTORY is not enabled");
    #endif
}


std::filesystem::path GetShaderPath(std::string file_name)
{
    // using namespace std::filesystem;
    // auto shadpath = GetCurrentPath();
    // shadpath = path("..") / path("shaders") / path(file_name);

    // return  shadpath;

     #ifdef SHADERS_DIRECTORY
        std::cout << "SHADERS_DIRECTORY :" << SHADERS_DIRECTORY << std::endl;
        return std::string(SHADERS_DIRECTORY) + std::string("/") + file_name;
    #else 
        throw std::exception("SHADERS_DIRECTORY is not enabled");
    #endif
}


}