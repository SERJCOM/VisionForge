#include "VisionForge/Engine/Environment.hpp"


using namespace vision;

vision::Environment::Environment(Shader* mainshader)
{
    skybox_ = std::make_unique<Skybox>(mainshader);
    light_manager_ = std::make_unique<LightManager>(*mainshader);
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
