#include <VisionForge/System/Shader.hpp>

#include <optional>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <spdlog/spdlog.h>

Shader::Shader(std::filesystem::path vertf, std::filesystem::path fragf)
{
    spdlog::info("Shader::Shader() : vert, frag");
    InitShader(vertf, fragf);
}

Shader::Shader(std::filesystem::path vertf, std::filesystem::path fragf, std::filesystem::path geomf)
{
    spdlog::info("Shader::Shader() : vert, frag, geom");

    unsigned int vertex, fragment, geom;

    std::string prog = ReadFile(vertf);
    const char *shaderCode = prog.c_str();
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &shaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    prog = ReadFile(fragf);
    shaderCode = prog.c_str();
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &shaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    prog = ReadFile(geomf);
    shaderCode = prog.c_str();
    geom = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geom, 1, &shaderCode, NULL);
    glCompileShader(geom);
    checkCompileErrors(geom, "GEOMETRY");

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glAttachShader(ID, geom);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    glDeleteShader(geom);
}

void Shader::InitShader(std::string vertf, std::string fragf)
{
    unsigned int vertex, fragment, geom;

    std::string prog = ReadFile(vertf);
    const char *shaderCode = prog.c_str();
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &shaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    prog = ReadFile(fragf);
    shaderCode = prog.c_str();
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &shaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value)
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, size_t value)
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), static_cast<GLint>(value));
}
void Shader::setFloat(const std::string &name, float value)
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, glm::mat4 &mat)
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setVec3(const std::string &name, glm::vec3 color)
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), color.r, color.g, color.b);
}

void Shader::setVec4(const std::string &name, float colorr, float colorg, float colorb, float colorw)
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), colorr, colorg, colorb, colorw);
}

void Shader::SetTexture(int index, int texture, std::string name)
{
    glActiveTexture(GL_TEXTURE0 + index);
    setInt(name.c_str(), index);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Shader::UseTexture(int index, int texture)
{
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Shader::SetCubeMapTexture(int index, int texture, std::string name)
{
    glActiveTexture(GL_TEXTURE0 + index);
    setInt(name, index);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
}

void Shader::SetUseMapTexture(int index, int texture, std::string name)
{
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
}

void Shader::AddSSBO(void *_ssbo, size_t size, int index)
{
    SSBO newssbo;
    newssbo.Init(_ssbo, size, index);
    ssbo.push_back(newssbo);
}

void Shader::BindSSBO()
{
    for (int i = 0; i < ssbo.size(); i++)
    {
        ssbo[i].Bind();
    }
}

void Shader::UseTexture(int number)
{
    glActiveTexture(GL_TEXTURE0 + number);
}

std::string Shader::ReadFile(std::filesystem::path path)
{
    std::string code;

    std::ifstream filestream(path);

    std::stringstream sstream;
    sstream << filestream.rdbuf();

    code = sstream.str();

    filestream.close();

    return code;
}

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            spdlog::critical("ERROR::SHADER_COMPILATION_ERROR of type: \n " + std::string(infoLog));
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            spdlog::critical("ERROR::PROGRAM_LINKING_ERROR of type: \n " + std::string(infoLog));
        }
    }
}
