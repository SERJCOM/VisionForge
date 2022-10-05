#pragma once
#include <iostream>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"


struct LightStruct{
    int type = 0;
    float ambient = 0;
    float specular = 0;
    glm::vec3 position = glm::vec3(50.0f, 50.0f, 50.0f);
    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

};

class LightManager{
public:
    LightManager(){
        lighting.reserve(16);
    }

    void AddLight(){
        LightStruct _light;
        lighting.push_back(_light);
    }

    void LinkShader(Shader* shader){
        this->shader = shader;
    }

    void SetShaderParameters(){
        shader->AddSSBO(lighting.data(), sizeof(LightStruct) * lighting.size(), 0);
        shader->use();
        shader->setInt("NUMBER_LIGHT", lighting.size());
    }

    LightStruct GetLight(int index){
        return lighting[index];
    }

private:
    Shader* shader = nullptr;

    std::vector<LightStruct> lighting;
};
