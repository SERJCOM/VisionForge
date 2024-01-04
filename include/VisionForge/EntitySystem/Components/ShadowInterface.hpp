#pragma once 

#include "VisionForge/EntitySystem/Component.hpp"

namespace vision{

class IShadow : public IComponent {
public:
    virtual ~IShadow() = default;

    virtual void Prepare() = 0;

    int GetShadowTexture() const{
        return depth_map_;
    }

    int width = 0;
    int height = 0;
    float far = 1.0f;
    float near = 1.0f;



protected:
    unsigned int depth_map_;

};



}