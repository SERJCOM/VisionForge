#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include <map>
#include <string>
#include <memory>
#include "collection.hpp"


class Light: public IComponent{
public:

    Light():type(1), ambient(0.8f), specular(0), position(glm::vec3(10.0f, 50.0f, 10.0f)), color(glm::vec3(1.0f, 1.0f, 1.0f)){};

    template<typename I, typename F, typename D>
    Light(I type, F ambient, D specular, glm::vec3 position,  glm::vec3 color): type(static_cast<int>(type)), ambient(static_cast<float>(ambient)), specular(static_cast<float>(specular)), position(position), color(color){}

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

class LightManager: public Collection{
public:
    LightManager() = default;

    Light* AddLight(int type, float ambient, float specular, glm::vec3 position, glm::vec3 color){
        Light _light(type, ambient, specular, position, color);
        return static_cast <Light*>(this->AddComponent(_light));
    }

    Light* AddLight(Light light){
        return static_cast <Light*>(this->AddComponent(light));
    }

    Light* AddLight(){
        return static_cast <Light*>(this->AddComponent());
    }

    void LinkShader(Shader* shader){
        this->shader = shader;
    }

    void SetShaderParameters() const{
        shader->use();
        int index = 0;
        for(const auto i : _components){
            shader->setFloat("point_light[" + std::to_string(index) + "].ambient" ,static_cast <Light*>(i.get())->GetAmbient());
            shader->setFloat("point_light[" + std::to_string(index) + "].specular" ,static_cast <Light*>(i.get())->GetSpecular());
            shader->setVec3("point_light[" + std::to_string(index) + "].pos", static_cast <Light*>(i.get())->GetPosition());
            shader->setVec3("point_light[" + std::to_string(index) + "].color", static_cast <Light*>(i.get())->GetColor());
            index++;
        }

        std::map<int, int> count;
        for(const auto& i : _components){
            count[static_cast <Light*>(i.get())->GetType()]++;
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
        return static_cast <Light*>(this->GetComponent(index));
    }

private:
    Shader* shader = nullptr;
};