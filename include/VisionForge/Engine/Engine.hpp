/*
This class is needed to control all Engine Modules except System module.
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
#include "VisionForge/Engine/LightManager.hpp"
#include "VisionForge/EntitySystem/VisualComponent.hpp"
#include "VisionForge/Engine/PostProcessing.hpp"



namespace vision
{

    class Engine
    {
        friend class System;

    public:

        void Display();

        template <typename T>
        T *RegistrateComponent();

        template <typename T>
        T *RegistrateEntity(std::string_view name);

        IEntity *GetEntity(std::string_view name) const;

        System *GetSystemPtr();

        Environment* GetEnvironmentPtr();

        IGameClass* GetGameClassPtr();

        PostProcessingManager* GetPostProcessingPtr();

        void SetGameClass(IGameClass* game);

        input::IInputManager* GetInputManagerPtr();

        void operator=(const Engine& engine) = delete;
        Engine(Engine& other) = delete;

        static Engine* GetInstance();

    protected:

        Engine();

        static Engine* engine_ptr_;

    private:

        

        template<typename T>
        void ProcessComponents(T func){
            for(auto& comp : components_){
                auto ptr = comp.get();
                func(ptr);
            }
        }

        template<typename T>
        void ProcessVisualComponents(T func){
            for(IComponent* comp : visual_components_){
                func(static_cast<IVisualComponent*>(comp));
            }
        }


        template<typename T>
        void ProcessEntities(T func){
            for(auto& comp : entities_){
                auto ptr = comp.get();
                func(ptr);
            }
        }

        // System* system_;
        std::unique_ptr<Environment> env_;
        std::unique_ptr<input::IInputManager> input_manager_;
        std::unique_ptr<PostProcessingManager> post_processing_manager_;

        std::vector<std::unique_ptr<IComponent>> components_;
        std::vector<std::unique_ptr<IEntity>> entities_;
        std::vector<IComponent*> visual_components_;
        std::unordered_map<std::string, IEntity *> name_entity_;


        IGameClass* game_class_ = nullptr;


        
    };



    template <typename T>
    T *Engine::RegistrateComponent()
    {
        auto t_ptr = std::make_unique<T>();

        if(dynamic_cast<IVisualComponent*>(t_ptr.get())){
            visual_components_.push_back(t_ptr.get());
        }
      
        components_.push_back(std::move(t_ptr));
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