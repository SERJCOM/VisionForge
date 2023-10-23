#pragma once

#include <functional>
#include "VisionForge/Common/Event.hpp"

namespace vision
{

    class IEntitySystem
    {
    public:
        virtual void Release() = 0; // 	Releases entity system.

        virtual void Update() = 0;

        virtual void Reset() = 0;

        virtual void AddEventListener(std::function<void(GameEvents)> &listener) = 0;

    private:
    };

    IEntitySystem *CreateEntitySystem();

}