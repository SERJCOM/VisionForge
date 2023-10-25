#pragma once

namespace vision
{

    class Environment;
    class Engine;

    class IComponent
    {
    public:
        IComponent() = default;

        ~IComponent() = default;

        virtual void Update() = 0;

        virtual void Start() = 0;

        void SetEnginePtr(Engine *sys)
        {
            gEngine = sys;
        }

    protected:
        Environment *gEnv = nullptr;
        Engine *gEngine = nullptr;

    private:
        void SetEnvironmentPtr(Environment *env)
        {
            gEnv = env;
        }
    };

}