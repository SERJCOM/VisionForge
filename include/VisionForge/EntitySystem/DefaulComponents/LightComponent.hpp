#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <map>
#include <string>
#include <memory>

#include "VisionForge/System/Shader.hpp"
#include "VisionForge/EntitySystem/Component.hpp"

namespace vision
{

    enum class LightType
    {
        POINT,
        
    };

    class Light : public IComponent
    {
    public:
        Light() = default;
        virtual ~Light() = default;


        glm::vec3 color = glm::vec3(1.0, 1.0, 1.0);
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        glm::vec3 brightness = glm::vec3(1, 1, 1);

    protected:
        LightType type_;
    };

    class PointLight : public Light
    {
    public:
        PointLight()
        {
            type_ = LightType::POINT;
        }

        virtual ~PointLight() = default;

        void Start() override
        {
        }

        void Update() override
        {
        }

        float constant;
        float linear;
        float quadratic;
    };

}
