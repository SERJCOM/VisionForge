#pragma once

#include "VisionForge/EntitySystem/Components/ShadowInterface.hpp"
#include "VisionForge/System/Framebuffer.hpp"
#include "VisionForge/System/Shader.hpp"
#include <vector>
#include <functional>
#include <string>
#include <algorithm>

#include "VisionForge/Common/Common.hpp"

namespace vision{

enum class ShadowType{
    POINT,
    FORWARD
};

class ShadowManager{
public:

    ShadowManager();

    void Start();

    template<typename T>
    T* AddShadow(ShadowType type);

    
    void PrepareShadows(std::function<void(Shader& shader)> func){


        framebuffer_->UseBuffer();



        for(int i = 0; i < std::min(point_shadows_.size(), (size_t)MAX_SHADOWS); i++){
            glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, point_shadows_[i]->GetShadowTexture(), 0);

            point_shadows_[i]->Prepare();
            func(point_shadows_[i]->GetShader());
        }

        framebuffer_->DontUseBuffer();

    }

    void UseShadows(Shader& shader);

private:

    void ProccessPointShadows(Shader& shader){
        int i = 0;

        shader.setInt("len_point_light_shadow", point_shadows_.size());
        
        std::string name_struct = "point_light_shadow";

        for(auto& point_ptr : point_shadows_){
            auto name_text_shader = name_struct + '[' + std::to_string(i) + ']';
            shader.setInt(name_text_shader + ".depthmap", 7 + i);
            shader.SetUseMapTexture(7 + i, point_ptr->GetShadowTexture() , name_text_shader + ".depthmap");

            shader.setFloat(name_text_shader + ".far_plane", point_ptr->far);
            shader.setVec3(name_text_shader + ".pos", point_ptr->GetObjectPosition());
            // std::cout << "позиция источника тени в использовании" << point_ptr->GetObjectPosition() << std::endl;
            i++;
        }
    }


    const int MAX_SHADOWS = 1;

    std::unique_ptr<FrameBuffer> framebuffer_;
    Shader shader;

    std::vector<std::unique_ptr<IShadow>> point_shadows_;

};

template <typename T>
inline T *ShadowManager::AddShadow(ShadowType type)
{
    point_shadows_.push_back(std::make_unique<T>());
    return static_cast<T*>(point_shadows_.back().get());
}

};