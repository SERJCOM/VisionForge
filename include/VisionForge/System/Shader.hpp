#pragma once

#include <string>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "VisionForge/System/Ssbo.hpp"
#include <filesystem>



class Shader
{
public:
    unsigned int ID;

    Shader() {}

    Shader(std::filesystem::path vertf, std::filesystem::path fragf);

    Shader(std::filesystem::path vertf, std::filesystem::path fragf, std::filesystem::path geomf);

    void InitShader(std::string vertf, std::string fragf);

    void use();

    void setBool(const std::string &name, bool value);

    void setInt(const std::string &name, size_t value);

    void setFloat(const std::string &name, float value);

    void setMat4(const std::string &name, glm::mat4 &mat);

    void setVec3(const std::string &name, glm::vec3 color);

    void setVec4(const std::string &name, float colorr, float colorg, float colorb, float colorw);

    void SetTexture(int index, int texture, std::string name);

    void UseTexture(int index, int texture);

    void SetCubeMapTexture(int index, int texture, std::string name);

    void SetUseMapTexture(int index, int texture, std::string name);

    void AddSSBO(void *_ssbo, size_t size, int index);

    void BindSSBO();

    void UseTexture(int number);

private:

    std::string ReadFile(std::filesystem::path path);

    void checkCompileErrors(unsigned int shader, std::string type);

    std::vector<SSBO> ssbo;
};