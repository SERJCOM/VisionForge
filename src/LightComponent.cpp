#include "VisionForge/Engine/Environment.hpp"
#include "VisionForge/EntitySystem/DefaulComponents/LightComponent.hpp"

using namespace vision;

void PointLightWithShadow::Start()
{
    p_shadow = gEnv->GetShadowManager()->AddShadow<vision::PointShadow>(vision::ShadowType::POINT);
    p_shadow->width = 1024;
    p_shadow->height = 1024;
    p_shadow->far = 250.0f;
}