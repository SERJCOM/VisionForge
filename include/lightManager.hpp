#pragma once
#include <iostream>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include <map>


struct LightStruct{
    int type = 0;
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
        if(light.type == 1) pointLightCount++;
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
        // std::map<int> count;
        // for(LightStruct i : lighting){
        //     count[i.type]++;
        // }
        // for(int i = 0; i < count.size(); i++){
        //     switch (i)
        //     {
        //     case 1:
        //         shader->setInt("len_point", )
        //         break;
            
        //     default:
        //         break;
        //     }
        // }
        if(pointLightCount > 0)     shader->setInt("len_point", pointLightCount);
    }

    LightStruct GetLight(int index){
        return lighting[index];
    }

private:
    Shader* shader = nullptr;

    std::vector<LightStruct> lighting;

    int pointLightCount = 0;
};