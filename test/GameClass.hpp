#pragma once

#include "VisionForge/Engine/GameClass.hpp"
#include "Entity.test.h"
#include "Model.test.h"

#include <filesystem>

class GameClass : public vision::IGameClass
{

public:
    void Start() override
    {

        using std::filesystem::path;

        test = gEngine->RegistrateEntity<test::Entity>("character");
        gEngine->GetSystemPtr()->SetMainCamera(test->GetCamera());

        mentity = gEngine->RegistrateEntity<MEntity>("mentity");

        std::filesystem::path test_dir = std::filesystem::current_path() / path("../test");

        gEngine->GetEnvironmentPtr()->GetSkyBoxPtr()->LoadSkyBox(test_dir / path("img") / path("moonless_golf_2k.hdr"));
    }

    void Update() override
    {
    }

private:
    test::Entity *test;

    MEntity *mentity;
};
