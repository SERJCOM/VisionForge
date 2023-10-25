#include "VisionForge/Engine/Engine.hpp"

#include "VisionForge/Engine/Shape.hpp"
#include "VisionForge/EntitySystem/DefaulComponents/LightComponent.hpp"

#include "Entity.test.h"
#include "Model.test.h"

using namespace std;
using namespace vision;

using filesystem::path;

int main()
{

    Engine engine;

    filesystem::path current_path = filesystem::current_path() / path("../shaders");
    current_path = current_path.lexically_normal();
    std::cout << current_path << std::endl;

    test::Entity *test = engine.RegistrateEntity<test::Entity>("test");
    engine.GetSystemPtr()->SetMainCamera(test->GetCamera());

    filesystem::path skybox_file = current_path / path("..") / path("test") / path("img") / path("small_empty_room_1_2k.hdr");
    skybox_file = skybox_file.lexically_normal();
    std::cout << skybox_file.c_str() << std::endl;
    Shape skybox;
    skybox.LoadRGBEfile(skybox_file.c_str());

    Shader &shad = engine.GetSystemPtr()->GetMainShader();
    shad.use();
    shad.SetCubeMapTexture(9, skybox.GetEnvironmentTexture(), "irradianceMap");
    shad.SetCubeMapTexture(10, skybox.GetPrefilterTexture(), "prefilterMap");
    shad.SetTexture(8, skybox.GetBDRFTexture(), "brdfLUT");

    System *system = engine.GetSystemPtr();

    bool running = true;

    auto loop = [&](int &drawning)
    {
        sf::Event event;
        while (engine.GetSystemPtr()->GetWindow().pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                drawning = 0;
        }

        skybox.DrawSkyBox(system->GetMainCamera()->GetViewMatrix(), system->GetProjectionMatrix());
    };

    engine.GetSystemPtr()->SetGameLoop(loop);

    engine.Display();

    return 0;
}