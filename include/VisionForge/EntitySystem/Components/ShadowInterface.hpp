#pragma once 

#include "VisionForge/EntitySystem/Component.hpp"
#include "VisionForge/System/Shader.hpp"
#include <string>

namespace vision{

class IShadow : public IComponent {
public:
    virtual ~IShadow() = default;

    virtual void Prepare() = 0;

    int GetShadowTexture() const{
        return depth_map_;
    }

    Shader& GetShader(){
        return shadow_shader;
    }

    virtual void UseShadow(Shader& shader) = 0;

    std::string GetNameStruct() const {
        return name_struct_;
    }

    int width = 0;
    int height = 0;
    float far = 1.0f;
    float near = 1.0f;



protected:
    unsigned int depth_map_;
    Shader shadow_shader;
    std::string name_struct_;

};



}