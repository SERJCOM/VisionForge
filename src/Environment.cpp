#include "VisionForge/Engine/Environment.hpp"

using namespace vision;

vision::Environment::Environment(Shader* mainshader)
{
    skybox_ = std::make_unique<Skybox>(mainshader);
}

vision::Environment::~Environment()
{
}

Skybox* Environment::GetSkyBoxPtr(){
    return skybox_.get();
}

