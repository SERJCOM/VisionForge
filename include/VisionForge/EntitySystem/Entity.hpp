#pragma once


#include "VisionForge/Common/Event.hpp"
#include "VisionForge/Engine/Object.hpp"

namespace vision
{

    class IEntity : public Object
    {

        friend class System;

    public:
        IEntity() = default;

        virtual void Update() = 0;
        virtual void Start() = 0;

        virtual void ProcessEvent(GameEvents event) = 0;

        virtual ~IEntity() = default;

        
    };

}