#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include <map>
#include <string>
#include <memory>
#include "component.hpp"


class Light{
public:
    Light():type(1), ambient(0.8), specular(0), position(glm::vec3(10.0f, 50.0f, 10.0f)), color(glm::vec3(1.0f, 1.0f, 1.0f)){};

    Light(int type, float ambient, float specular, glm::vec3 position,  glm::vec3 color): type(type), ambient(ambient), specular(specular), position(position), color(color){}

    void SetType(int type) {this->type = type;}
    void SetAmbient(float ambient) {this->ambient = ambient;}
    void SetSpecular(float specular) {this->specular = specular;}
    void SetPosition(glm::vec3 position) {this->position = position;}
    void SetColor(glm::vec3 color) {this->color = color;}

    int GetType() {return this->type;}
    float GetAmbient() {return this->ambient;}
    float GetSpecular() {return this->specular;}
    glm::vec3 GetPosition() {return this->position;}
    glm::vec3 GetColor() {return this->color;}

private: 
    int type ;
    float ambient ;
    float specular ;
    glm::vec3 position ;
    glm::vec3 color;
};

class LightManager: public Component<Light>{
public:
    LightManager() = default;

    Light* AddLight(int type, float ambient, float specular, glm::vec3 position, glm::vec3 color){
        Light _light;
        return this->AddComponent(_light);
    }

    Light* AddLight(Light light){
        return this->AddComponent(light);
    }

    Light* AddLight(){
        return this->AddComponent();
    }

    void LinkShader(Shader* shader){
        this->shader = shader;
    }

    void SetShaderParameters() const{
        shader->use();
        int index = 0;
        for(const auto i : _components){
            shader->setFloat("point_light[" + std::to_string(index) + "].ambient" ,i->GetAmbient());
            shader->setFloat("point_light[" + std::to_string(index) + "].specular" ,i->GetSpecular());
            shader->setVec3("point_light[" + std::to_string(index) + "].pos", i->GetPosition());
            shader->setVec3("point_light[" + std::to_string(index) + "].color", i->GetColor());
            index++;
        }

        std::map<int, int> count;
        for(const auto& i : _components){
            count[i.get()->GetType()]++;
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

    Light* GetLight(int index) const{
        return this->GetComponent(index);
    }

private:
    Shader* shader = nullptr;
};