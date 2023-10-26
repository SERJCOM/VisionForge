#pragma once

#include "VisionForge/Engine/Object.hpp"

namespace vision
{

    class IComponent : public Object
    {
    public:
        IComponent() = default;

        virtual ~IComponent() = default;

        IComponent& operator=(IComponent&) = delete;
        IComponent(IComponent&) = delete;

        virtual void Update() = 0;

        virtual void Start() = 0;

    };

}