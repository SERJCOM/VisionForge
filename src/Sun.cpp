#include "VisionForge/Engine/PostProc/Sun.hpp"
#include "VisionForge/Engine/Engine.hpp"
#include "VisionForge/Common/Common.hpp"


void vision::post::Sun::Start()
{
    SetPath(GetBuildPath() / "ball.fbx");
    LoadModel();

    SetObjectPosition(glm::vec3(100, 100, 100));
    SetObjectSize(glm::vec3(10, 10, 10));

}

// void vision::post::Sun::Update()
// {
// }