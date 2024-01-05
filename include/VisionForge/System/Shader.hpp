#pragma once
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "VisionForge/System/Ssbo.hpp"
#include <filesystem>
#include <optional>

class Shader
{
public:
    unsigned int ID;

    Shader() {}

    Shader(std::filesystem::path vertf, std::filesystem::path fragf)
    {
        InitShader(vertf, fragf);
    }

    Shader(std::filesystem::path vertf, std::filesystem::path fragf, std::filesystem::path geomf)
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

    void InitShader(std::string vertf, std::string fragf)
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

    void use()
    {
        glUseProgram(ID);
    }

    void setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    void setInt(const std::string &name, size_t value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), static_cast<GLint>(value));
    }
    void setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setMat4(const std::string &name, glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    void setVec3(const std::string &name, glm::vec3 color) const
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), color.r, color.g, color.b);
    }

    void setVec4(const std::string &name, float colorr, float colorg, float colorb, float colorw) const
    {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), colorr, colorg, colorb, colorw);
    }

    void SetTexture(int index, int texture, std::string name)
    {
        glActiveTexture(GL_TEXTURE0 + index);
        setInt(name.c_str(), index);
        glBindTexture(GL_TEXTURE_2D, texture);
    }


    void UseTexture(int index, int texture)
    {
        glActiveTexture(GL_TEXTURE0 + index);
        glBindTexture(GL_TEXTURE_2D, texture);
    }

    void SetCubeMapTexture(int index, int texture, std::string name)
    {
        glActiveTexture(GL_TEXTURE0 + index);
        setInt(name, index);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    }

    void SetUseMapTexture(int index, int texture, std::string name)
    {
        glActiveTexture(GL_TEXTURE0 + index);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    }

    void AddSSBO(void *_ssbo, size_t size, int index)
    {
        SSBO newssbo;
        newssbo.Init(_ssbo, size, index);
        ssbo.push_back(newssbo);
    }

    void BindSSBO()
    {
        for (int i = 0; i < ssbo.size(); i++)
        {
            ssbo[i].Bind();
        }
    }

    void UseTexture(int number)
    {
        glActiveTexture(GL_TEXTURE0 + number);
    }

private:

    std::string ReadFile(std::filesystem::path path){
        std::string code;

        std::ifstream filestream(path);

        std::stringstream sstream ;
        sstream << filestream.rdbuf();

        code = sstream.str();

        return code;
    }

    void checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                          << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                          << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }

    std::vector<SSBO> ssbo;
};