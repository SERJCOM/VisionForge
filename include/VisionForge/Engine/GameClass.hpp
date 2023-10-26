#pragma once

namespace vision
{

    class Environment;
    class Engine;

    class IGameClass
    {
    public:
        IGameClass() = default;
        virtual ~IGameClass() = default;

        virtual void Start() = 0;

        virtual void Update() = 0;

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
    };

}