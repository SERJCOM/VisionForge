#pragma once
#include "VisionForge/EntitySystem/Component.hpp"

namespace vision{

    class ICameraComponents : public IComponent{
        public:

        virtual void Looking() = 0;

        virtual glm::mat4 GetViewMatrix() const = 0;

        virtual glm::vec3 GetCameraUp() const = 0;

        virtual glm::vec3 GetCameraFront() const = 0;

    };

}