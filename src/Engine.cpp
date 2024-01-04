#include "VisionForge/Engine/Engine.hpp"




using namespace vision;

vision::Engine::Engine()
{
    system_ = std::make_unique<System>();
    system_->SetEnginePtr(this);

    env_ = std::make_unique<Environment>(&GetSystemPtr()->GetMainShader());

    input_manager_ = input::CreateBasicInputManager();
}

void vision::Engine::Display()
{
    if(game_class_ == nullptr){
        std::cerr << "ERROR!!! Missing main class" << std::endl;
        assert(false);
    }

    game_class_->Start();
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

IGameClass *vision::Engine::GetGameClassPtr()
{
    return game_class_;
}
void vision::Engine::SetGameClass(vision::IGameClass *game)
{
    game_class_ = game;
    game_class_->SetEnginePtr(this);
    game_class_->SetEnvironmentPtr(env_.get());
}

input::IInputManager *vision::Engine::GetInputManagerPtr()
{
    return input_manager_.get();
}
