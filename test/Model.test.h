#pragma once
#include "Entity.hpp"
#include "model.h"
#include <memory>
#include "Engine.h"
#include "material.hpp"
#include <iostream>
#include "mesh.hpp"

class MEntity : public lthm::IEntity{
public:

    MEntity(lthm::Engine& engine, std::filesystem::path model_path){


        engine_ = &engine;

        mesh.Create2DRectangle();

        // std::shared_ptr<lthm::ModelComponent> _model = std::make_shared<lthm::ModelComponent>(model_path.c_str());

        // _model->ScaleObject(glm::vec3{100, 100, 100});
        // _model->SetShader(engine.GetMainShader());
        // _model->MoveObject(0, -100, 0);
        // _model->LoadModel();

        // auto materialpath = std::filesystem::current_path() / std::filesystem::path("../test/obj/dimaMap/map_color.png");
        // materialpath.lexically_normal();
        // std::cout << "materialpath " << materialpath.c_str() << std::endl;
        // Li::Material matHouse;
        // matHouse.AddNewMaterial(model_path.c_str() , Li::Type::DIFFUSE, "Default_OBJ");
        // _model->AddMaterial(&matHouse);

        // model = std::move(_model);

    }

    void Start() override{
        
    }

    void Update() override{
        mesh.DrawRectangle(engine_->GetMainShader(), 0);
    }

    std::vector<std::shared_ptr<lthm::IComponent>> GetComponents() const override {
        std::vector<std::shared_ptr<lthm::IComponent>> res;

        // res.push_back(model);

        return res;
    }

    // lthm::CameraComponent* GetCamera() const {
    //     return static_cast<lthm::CameraComponent*>(camera.get());
    // }


private:
Mesh mesh;
lthm::Engine* engine_;
};