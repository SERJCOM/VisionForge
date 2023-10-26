#pragma once

#include "VisionForge/Engine/GameClass.hpp"
#include "Entity.test.h"
#include "Model.test.h"


class GameClass : public vision::IGameClass
{

public:
    void Start() override
    {
        test = gEngine->RegistrateEntity<test::Entity>("character");
        gEngine->GetSystemPtr()->SetMainCamera(test->GetCamera());
    }

    void Update() override
    {
    }

private:
    test::Entity *test;
};
