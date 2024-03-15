/*
LightManager is needed to controll all light in the scene
LightManager belongs to Environment class
*/

#pragma once

#include <vector>
#include <memory>

#include "VisionForge/EntitySystem/DefaulComponents/LightComponent.hpp"
#include "VisionForge/System/Shader.hpp"

namespace vision
{

    struct NameFieldValue
    {
        std::string name;
        std::string field;
        double value;
    };

    class Environment;
    class Engine;

    class LightManager
    {
    public:
        LightManager(Shader &shader, Environment *env)
        {
            shader_ = &shader;
            // gEngine = engine;
            gEnv = env;
        }

        template <typename T>
        T *AddLight()
        {
            lights_.push_back(std::make_unique<T>());
            // lights_.back()->SetEnginePtr(gEngine);
            lights_.back()->SetEnvironmentPtr(gEnv);
            lights_.back()->Start();

            return static_cast<T *>(lights_.back().get());
        }

        void Update()
        {
            for (int i = 0; i < lights_.size(); i++)
            {
                lights_[i]->Update();
            }
        }

        void Draw()
        {
            Update();
            shader_->use();
            shader_->setInt("len_point", lights_.size());
            for (int i = 0; i < lights_.size(); i++)
            {
                std::string id = std::to_string(i);
                shader_->setVec3("point_light[" + id + "].pos", lights_[i]->GetObjectPosition());
                shader_->setVec3("point_light[" + id + "].color", lights_[i]->color);
                shader_->setVec3("point_light[" + id + "].brightness", lights_[i]->brightness);
            }
        }

    private:
        Shader *shader_;
        std::vector<std::unique_ptr<Light>> lights_;
        // Engine* gEngine;
        Environment *gEnv;
    };

}