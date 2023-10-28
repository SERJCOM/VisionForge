#pragma once
#include <memory>

#include "VisionForge/EntitySystem/Component.hpp"
#include "VisionForge/EntitySystem/Entity.hpp"
#include "VisionForge/Engine/Skybox.hpp"
#include "VisionForge/System/Shader.hpp"
#include "VisionForge/Engine/LightManager.hpp"

namespace vision
{

    class Environment 
    {
    public:
        Environment(Shader* mainshader);

        virtual ~Environment();

        Skybox* GetSkyBoxPtr();

        LightManager* GetLightManagerPtr();

    private:
        std::unique_ptr<Skybox> skybox_;
        std::unique_ptr<LightManager> light_manager_;
        Shader* main_shader_ = nullptr;

    };

}