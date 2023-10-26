#pragma once

#include <string>

#include "Component.hpp"
#include "VisionForge/Common/Event.hpp"

namespace vision
{

    class Environment;
    class Engine;

    class IEntity
    {

        friend class System;

    public:
        IEntity() = default;

        virtual void Update() = 0;
        virtual void Start() = 0;

        virtual void ProcessEvent(GameEvents event) = 0;

        virtual ~IEntity() = default;

        std::string GetName() const;
        void SetName(std::string classname);

        void SetEnginePtr(Engine *sys)
        {
            gEngine = sys;
        }

        void SetEnvironmentPtr(Environment *env){
            gEnv = env;
        }

    protected:
        Environment *gEnv = nullptr;
        Engine *gEngine = nullptr;

        std::string name;

    private:
        
    };

}