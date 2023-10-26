#pragma once

namespace vision
{

    class Environment;
    class Engine;

    class IComponent
    {
    public:
        IComponent() = default;

        virtual ~IComponent() = default;

        IComponent& operator=(IComponent&) = delete;
        IComponent(IComponent&) = delete;

        virtual void Update() = 0;

        virtual void Start() = 0;

        void SetEnginePtr(Engine *sys)
        {
            gEngine = sys;
        }

        void SetEnvironmentPtr(Environment *env)
        {
            gEnv = env;
        }

    protected:
        Environment *gEnv = nullptr;
        Engine *gEngine = nullptr;

    private:
        
    };

}