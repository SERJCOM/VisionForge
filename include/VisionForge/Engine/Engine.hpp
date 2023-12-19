/*
A class is needed to control all Engine Modules except System module.
The class assignment is Registration Components, Entities, Displaying , and other.
the pattern is Facade-Singleton

meanwhile the System module controls only visualization
*/

#pragma once

#include <string>
#include <string_view>
#include <memory>
#include <vector>
#include <unordered_map>
#include <cassert>

#include "VisionForge/System/System.hpp"
#include "VisionForge/EntitySystem/Entity.hpp"
#include "VisionForge/EntitySystem/Component.hpp"
#include "VisionForge/Engine/Environment.hpp"
#include "VisionForge/Engine/GameClass.hpp"
#include "VisionForge/Common/InputManager.hpp"

namespace vision
{

    class Engine
    {
        friend class System;

    public:

        Engine();

        void Display();

        template <typename T>
        T *RegistrateComponent();

        template <typename T>
        T *RegistrateEntity(std::string_view name);

        IEntity *GetEntity(std::string_view name) const;

        System *GetSystemPtr();

        Environment* GetEnvironmentPtr();

        IGameClass* GetGameClassPtr();

        void SetGameClass(IGameClass* game);

        input::IInputManager* GetInputManager();

        

    private:
        std::unique_ptr<System> system_;
        std::unique_ptr<Environment> env_;
        std::unique_ptr<input::IInputManager> input_manager_;

        std::vector<std::unique_ptr<IComponent>> components_;
        std::vector<std::unique_ptr<IEntity>> entities_;
        std::unordered_map<std::string, IEntity *> name_entity_;


        IGameClass* game_class_ = nullptr;
    };



    template <typename T>
    T *Engine::RegistrateComponent()
    {
        components_.push_back(std::make_unique<T>());
        components_.back()->SetEnginePtr(this);
        components_.back()->SetEnvironmentPtr(env_.get());
        components_.back()->Start();
        return static_cast<T *>(components_.back().get());
    }

    template <typename T>
    T *Engine::RegistrateEntity(std::string_view name)
    {
        if (name_entity_.count(name.data()) != 0)
        {
            std::cerr << "Error!!! The name is already using" << std::endl;
            assert(false);
        }

        entities_.push_back(std::make_unique<T>());
        name_entity_[name.data()] = entities_.back().get();
        entities_.back()->SetEnginePtr(this);
        entities_.back()->SetEnvironmentPtr(env_.get());
        entities_.back()->Start();
        return static_cast<T *>(entities_.back().get());
    }
}