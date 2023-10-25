// #pragma once

// #include "VisionForge/EntitySystem/DefaulComponents/ModelComponent.hpp"
// #include <memory>
// #include "VisionForge/System/System.hpp"
// #include "VisionForge/Engine/Material.hpp"
// #include <iostream>


// //#include "VisionForge/EntitySystem/DefaulComponents/LightComponent.hpp"

// class MEntity : public vision::IEntity{
// public:

//     MEntity(vision::System& engine, std::filesystem::path model_path){

//         using std::filesystem::path;

//         std::shared_ptr<vision::ModelComponent> _model = std::make_shared<vision::ModelComponent>(model_path.c_str());

//         // Li::Material material;
//         // material.AddNewMaterial(model_path.parent_path() / path("Bank_Beer_BaseColor.png"), Li::Type::DIFFUSE, "blinn3");
//         // material.AddNewMaterial(model_path.parent_path() / path("Bank_Beer_Metallic.png"), Li::Type::METALNESS, "blinn3");
//         // material.AddNewMaterial(model_path.parent_path() / path("Bank_Beer_Normal.png"), Li::Type::NORMALS, "blinn3");
//         // material.AddNewMaterial(model_path.parent_path() / path("Bank_Beer_Roughness.png"), Li::Type::ROUGHNESS, "blinn3");

//         // _model->ScaleObject(glm::vec3{10, 10, 10});
//         // _model->AddMaterial(&material);
//         _model->SetShader(engine.GetMainShader());
//         _model->MoveObject(0, 0, 0);
//         _model->LoadModel();

//         model = std::move(_model);

//         // std::shared_ptr<vision::LightComponent> _light = std::make_shared<vision::LightComponent>();

//     }

//     void Start() override{
        
//     }

//     void Update() override{

//     }

//     void ProcessEvent(vision::GameEvents event) override {

//     }


//     // vision::CameraComponent* GetCamera() const {
//     //     return static_cast<vision::CameraComponent*>(camera.get());
//     // }


// private:
// std::shared_ptr<vision::ModelComponent> model;
// // std::shared_ptr<vision::IComponent> light;

// };