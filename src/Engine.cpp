#include "VisionForge/Engine/Engine.hpp"

#include <spdlog/spdlog.h>
#include "spdlog/sinks/basic_file_sink.h" // support for basic file logging
// #include "Engine.hpp"

using namespace vision;

vision::Engine::Engine()
{
    // auto my_logger = spdlog::basic_logger_mt("basic_logger", "logs/basic.txt");

    // spdlog::set_default_logger(my_logger);

    spdlog::info("Engine::Engine()");

    // system_ = System::GetInstance();
    // system_->SetEnginePtr(this);

    env_ = std::make_unique<Environment>(&GetSystemPtr()->GetMainShader());

    post_processing_manager_ = std::make_unique<PostProcessingManager>();

    input_manager_ = input::CreateBasicInputManager();
}

void vision::Engine::Display()
{
    spdlog::info("Engine::Display()");

    if (game_class_ == nullptr)
    {
        std::cerr << "ERROR!!! Missing main class" << std::endl;
        spdlog::critical("Engine::Display() -> ERROR!!! Missing main class");
        assert(false);
    }

    game_class_->Start();
    post_processing_manager_->Start();
    
    System::GetInstance()->Start();
    System::GetInstance()->Display();
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
    return System::GetInstance();
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


Engine* Engine::engine_ptr_ = nullptr;

vision::Engine *vision::Engine::GetInstance()
{
    if(!engine_ptr_){
        engine_ptr_ = new Engine();
    }

    return engine_ptr_;
}


PostProcessingManager* Engine::GetPostProcessingPtr(){
    return post_processing_manager_.get();
}