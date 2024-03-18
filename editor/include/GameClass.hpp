#pragma once

#include <VisionForge/Engine/Engine.hpp>
#include <VisionForge/Engine/GameClass.hpp>
#include <VisionForge/EntitySystem/Component.hpp>
#include <VisionForge/EntitySystem/DefaulComponents/CameraComponent.hpp>
// #include "Entity.test.h"
// #include "Model.test.h"

#include <filesystem>

class GameClass : public vision::IGameClass
{

public:
    void Start() override
    {

        using std::filesystem::path;

        // test = gEngine->RegistrateEntity<test::Entity>("character");
        test = vision::Engine::GetInstance()->RegistrateComponent<vision::CameraComponent>();
        vision::Engine::GetInstance()->GetSystemPtr()->SetMainCamera(test);

        // mentity = gEngine->RegistrateEntity<MEntity>("mentity");

        // std::filesystem::path test_dir = std::filesystem::current_path() / path("../test");

        // gEngine->GetEnvironmentPtr()->GetSkyBoxPtr()->LoadSkyBox(test_dir / path("assets") / path("textures") / path("moonless_golf_4k.hdr"));
    }

    void Update() override
    {
    }

private:
    vision::CameraComponent *test;

    // MEntity *mentity;
};
