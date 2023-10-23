#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "VisionForge/System/Shader.hpp"
#include <map>
#include <string>
#include <memory>
#include "VisionForge/EntitySystem/Component.hpp"

namespace vision{

class LightComponent: public vision::IComponent{
public:

    LightComponent():type(1), ambient(0.8f), specular(0), position(glm::vec3(10.0f, 50.0f, 10.0f)), color(glm::vec3(1.0f, 1.0f, 1.0f)){
        id_++;
    };

    template<typename I, typename F, typename D>
    LightComponent(I type, F ambient, D specular, glm::vec3 position,  glm::vec3 color): type(static_cast<int>(type)), 
    ambient(static_cast<float>(ambient)), specular(static_cast<float>(specular)), 
    position(position), color(color){
        id_++;
    }

    LightComponent(int type, float ambient, float specular, glm::vec3 position,  glm::vec3 color): type(type), ambient(ambient), 
    specular(specular), position(position), color(color){
        id_++;
    }

    ~LightComponent(){
        id_--;
    }
    
    void SetType(int type) {this->type = type;}
    void SetAmbient(float ambient) {this->ambient = ambient;}
    void SetSpecular(float specular) {this->specular = specular;}
    void SetPosition(glm::vec3 position) {this->position = position;}
    void SetColor(glm::vec3 color) {this->color = color;}

    void SetShader(Shader* shader){ shader_ = shader; }

    void Start() override {

    }

    void Update() override {

    }

    static int GetId() {
        return id_;
    }

    int GetType() {return this->type;}
    float GetAmbient() {return this->ambient;}
    float GetSpecular() {return this->specular;}
    glm::vec3 GetPosition() {return this->position;}
    glm::vec3 GetColor() {return this->color;}

private: 
    Shader* shader_ = nullptr;
    int type ;
    float ambient ;
    float specular ;
    glm::vec3 position ;
    glm::vec3 color;
    static int id_ ;
};



}

// class LightManager: public Collection{
// public:
//     LightManager() = default;

//     Light* AddLight(int type, float ambient, float specular, glm::vec3 position, glm::vec3 color){
//         SetUpdate();
//         Light _light(type, ambient, specular, position, color);
//         return static_cast <Light*>(this->AddComponent(_light));
//     }

//     Light* AddLight(Light light){
//         SetUpdate();
//         return static_cast <Light*>(this->AddComponent(light));  
//     }

//     Light* AddLight(){
//         SetUpdate();
//         return static_cast <Light*>(this->AddComponent());
//     }

//     void LinkShader(Shader* shader){
//         this->shader = shader;
//         SetUpdate();
//     }

//     void SetShaderParameters() const{
//         shader->use();
//         int index = 0;
//         for(const auto i : _components){
//             shader->setFloat("point_light[" + std::to_string(index) + "].ambient" ,static_cast <Light*>(i.get())->GetAmbient());
//             shader->setFloat("point_light[" + std::to_string(index) + "].specular" ,static_cast <Light*>(i.get())->GetSpecular());
//             shader->setVec3("point_light[" + std::to_string(index) + "].pos", static_cast <Light*>(i.get())->GetPosition());
//             shader->setVec3("point_light[" + std::to_string(index) + "].color", static_cast <Light*>(i.get())->GetColor());
//             index++;
//         }

//         std::map<int, int> count;
//         for(const auto& i : _components){
//             count[static_cast <Light*>(i.get())->GetType()]++;
//         }
//         for(auto i : count){
//             switch (i.first)
//             {
//             case 1:
//                 shader->setInt("len_point", i.second);
//                 break;
//             }
//         }
//     }

//     Light* GetLight(int index) const{
//         return static_cast <Light*>(this->GetComponent(index));
//     }

//     virtual void Update() override{
//         if(WasUpdated == true){
//             SetShaderParameters();
//         }
//         WasUpdated = false;
//     }

// private:
//     Shader* shader = nullptr;

//     bool WasUpdated = false;

//     void SetUpdate(){
//         WasUpdated = true;
//     }
// };