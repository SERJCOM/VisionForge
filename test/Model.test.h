#pragma once

#include <memory>
#include <iostream>
#include <filesystem>

#include "VisionForge/EntitySystem/DefaulComponents/ModelComponent.hpp"
#include "VisionForge/System/System.hpp"
#include "VisionForge/Engine/Material.hpp"
#include "VisionForge/Engine/Engine.hpp"



class MEntity : public vision::IEntity{
public:

MEntity(){


}

void Start() override{

    using std::filesystem::path;

    model = gEngine->RegistrateComponent<vision::ModelComponent>();

    auto dir_path = std::filesystem::current_path() / path("..") / path("test") / path("assets") / path("models") / path("cubes") ;

    model->SetPath(dir_path / path("cubes.obj"));

    // model1 = gEngine->RegistrateComponent<vision::ModelComponent>();
    // model1->SetPath(std::filesystem::current_path() / path("ball.fbx"));

    // vision::Material mat;
    // mat.AddNewMaterial(dir_path  /  path("D.png"), vision::Type::DIFFUSE, "DefaultMaterial");
    // mat.AddNewMaterial(dir_path  /  path("Metal.png"), vision::Type::METALNESS, "DefaultMaterial");
    // mat.AddNewMaterial(dir_path  /  path("N.png"), vision::Type::NORMALS, "DefaultMaterial");
    // mat.AddNewMaterial(dir_path  /  path("rough.png"), vision::Type::ROUGHNESS, "DefaultMaterial");


    // model->AddMaterial(&mat );
    // model->ScaleObject(glm::vec3(1, 1, 1));
    // model->SetObjectSize(glm::vec3(0.01, 0.01, 0.01));
    model->SetObjectPosition(glm::vec3(50, 50, 50));
    model->LoadModel();


    // vision::Material mat1;

    // model1->MoveObject(glm::vec3(15, 15, 15));

    // vision::Material mat;

    // mat.AddNewMaterial(glm::vec3(100, 100, 100), vision::Type::DIFFUSE, "white");

    // model1->LoadModel();

    
}

void Update() override{
    i+= 1;



}

void ProcessEvent(vision::GameEvents event) override {

}


private:
vision::ModelComponent* model;
vision::ModelComponent* model1;
vision::ModelComponent* room;

vision::ModelComponent* house;
double i = 0;

};