#pragma once

#include "VisionForge/EntitySystem/Components/ShadowInterface.hpp"
#include "VisionForge/System/Framebuffer.hpp"
#include "VisionForge/System/Shader.hpp"
#include <vector>

namespace vision{

class ShadowManager{
public:

    ShadowManager();

    // void Start();

    template<typename T>
    T* AddShadow();

    void PrepareShadows();

    void UseShadows();

private:
    std::unique_ptr<FrameBuffer> framebuffer_;
    Shader shader;
    std::vector<std::unique_ptr<IShadow>> shadows_;

};

template <typename T>
inline T *ShadowManager::AddShadow()
{
    shadows_.push_back(std::make_unique<T>());
    return static_cast<T*>(shadows_.back().get());
}

};