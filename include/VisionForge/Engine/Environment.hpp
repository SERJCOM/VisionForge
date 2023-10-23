#pragma once
#include "VisionForge/EntitySystem/Component.hpp"
#include "VisionForge/EntitySystem/Entity.hpp"
#include <memory>

namespace vision
{

    class Environment
    {
    public:
        Environment(/* args */);

        virtual ~Environment();

        template <typename T, typename... Y>
        std::shared_ptr<IComponent> GetOrCreateComponent(Y &&...y);

    protected:
    };

    template <typename T, typename... Y>
    inline std::shared_ptr<IComponent> Environment::GetOrCreateComponent(Y &&...y)
    {
    }

}