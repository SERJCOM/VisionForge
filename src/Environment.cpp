#include "VisionForge/Engine/Environment.hpp"


using namespace vision;

vision::Environment::Environment(Shader* mainshader)
{
    skybox_ = std::make_unique<Skybox>(mainshader);
    light_manager_ = std::make_unique<LightManager>(*mainshader);
    shadow_manager_ = std::make_unique<ShadowManager>();
}

vision::Environment::~Environment()
{
}

Skybox* Environment::GetSkyBoxPtr(){
    return skybox_.get();
}

LightManager *vision::Environment::GetLightManagerPtr()
{
    return light_manager_.get();
}
ShadowManager *vision::Environment::GetShadowManager()
{
    return shadow_manager_.get();
}
