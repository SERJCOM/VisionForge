#pragma once
#include <iostream>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"

struct LightStruct{
    float ambient;
    float specular;
    glm::vec3 color = glm::vec3(1.0, 1.0, 1.0);

    void Set(float ambient, float specular, glm::vec3 color){
        this->ambient = ambient;
        this->specular = specular;
        this->color = color;
    }
};

class LightManager{
public:
    LightManager(){
        lighting.reserve(16);
        std::cout << sizeof(LightStruct) << " size" << std::endl;
    }

    void AddLight(){
        LightStruct _light;
        lighting.push_back(_light);
        std::cout << lighting.size() << " size" << std::endl;
    }

    void LinkShader(Shader* shader){
        this->shader = shader;
    }

    void SetShaderParameters(){
        shader->AddSSBO(lighting.data(), (int)sizeof(lighting) * lighting.size(), 0);
    }

    LightStruct GetLight(int index){
        return lighting[index];
    }

private:
    Shader* shader = nullptr;

    std::vector<LightStruct> lighting;
};
