#pragma once 
#include "VisionForge/EntitySystem/Component.hpp"
#include "VisionForge/System/Shader.hpp"

namespace vision{

class IVisualComponent : public IComponent{
public:

    virtual void Draw(Shader& shader) = 0;


};

}