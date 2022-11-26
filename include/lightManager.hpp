#pragma once
#include <iostream>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include <map>
#include <string>


struct LightStruct{
    int type = 1;
    float ambient = 0.8f;
    float specular = 0;
    glm::vec3 position = glm::vec3(10.0f, 50.0f, 10.0f);
    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
};

class LightManager{
public:
    LightManager(){
        lighting.reserve(16);
    }

    void AddLight(int type, float ambient, float specular, glm::vec3 position, glm::vec3 color){
        LightStruct _light;
        _light.type = type;
        _light.ambient = ambient;
        _light.specular = specular;
        _light.position = position;
        _light.color = color;
        lighting.push_back(_light);
    }

    void AddLight(LightStruct light){
        LightStruct _light = light;
        lighting.push_back(_light);
    }

    void AddLight(){
        LightStruct _light;
        lighting.push_back(_light);
    }

    void LinkShader(Shader* shader){
        this->shader = shader;
    }

    void SetShaderParameters(){
        shader->use();
        int index = 0;
        for(LightStruct i : lighting){
            shader->setFloat("point_light[" + std::to_string(index) + "].ambient" ,i.ambient);
            shader->setFloat("point_light[" + std::to_string(index) + "].specular" ,i.specular);
            shader->setVec3("point_light[" + std::to_string(index) + "].pos", i.position);
            shader->setVec3("point_light[" + std::to_string(index) + "].color", i.color);
            index++;
        }

        std::map<int, int> count;
        for(LightStruct i : lighting){
            count[i.type]++;
        }
        for(auto i : count){
            switch (i.first)
            {
            case 1:
                shader->setInt("len_point", i.second);
                break;
            }
        }
    }

    LightStruct GetLight(int index){
        return lighting[index];
    }

private:
    Shader* shader = nullptr;

    std::vector<LightStruct> lighting;

    int pointLightCount = 0;
};