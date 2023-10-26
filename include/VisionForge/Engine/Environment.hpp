#pragma once
#include <memory>

#include "VisionForge/EntitySystem/Component.hpp"
#include "VisionForge/EntitySystem/Entity.hpp"
#include "VisionForge/Engine/Skybox.hpp"
#include "VisionForge/System/Shader.hpp"

namespace vision
{

    class Environment 
    {
    public:
        Environment(Shader* mainshader);

        virtual ~Environment();

        Skybox* GetSkyBoxPtr();

    private:
        std::unique_ptr<Skybox> skybox_;
        Shader* main_shader_ = nullptr;

    };

}