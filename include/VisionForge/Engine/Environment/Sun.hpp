#pragma once 

#include <VisionForge/System/Shader.hpp>
#include <VisionForge/Engine/Object.hpp>

namespace vision{

class Sun : public Object{
public:

void SetShader(Shader* shader){
    shader_ = shader;
}

void ShadowsMode(bool flag);

void Update();

private:

Shader* shader_;

};

}