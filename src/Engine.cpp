#include "VisionForge/Engine/Engine.hpp"


using namespace vision;

vision::Engine::Engine()
{
    system_ = std::make_unique<System>();
    system_->SetEnginePtr(this);

    env_ = std::make_unique<Environment>(&GetSystemPtr()->GetMainShader());
}

void vision::Engine::Display()
{
    system_->Display();
}

IEntity *vision::Engine::GetEntity(std::string_view name) const
{
    if (name_entity_.count(name.data()) == 0)
    {
        return nullptr;
    }

    return name_entity_.at(name.data());
}

System *vision::Engine::GetSystemPtr()
{
    return system_.get();
}
Environment *vision::Engine::GetEnvironmentPtr()
{
    return env_.get();
}
