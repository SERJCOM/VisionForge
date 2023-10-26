#include "VisionForge/Engine/Engine.hpp"

#include "VisionForge/Engine/Skybox.hpp"
#include "VisionForge/EntitySystem/DefaulComponents/LightComponent.hpp"

#include "GameClass.hpp"

using namespace std;
using namespace vision;

using filesystem::path;

int main()
{

    Engine engine;

    System *system = engine.GetSystemPtr();

    filesystem::path current_path = filesystem::current_path() / path("../shaders");
    current_path = current_path.lexically_normal();
    filesystem::path skybox_file = current_path / path("..") / path("test") / path("img") / path("small_empty_room_1_2k.hdr");
    skybox_file = skybox_file.lexically_normal();

    engine.GetEnvironmentPtr()->GetSkyBoxPtr()->LoadSkyBox(skybox_file.c_str());

    GameClass game;
    engine.SetGameClass(&game);

    bool running = true;

    auto loop = [&](int &drawning)
    {
        sf::Event event;
        while (engine.GetSystemPtr()->GetWindow().pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                drawning = 0;
        }
    };

    engine.GetSystemPtr()->SetGameLoop(loop);

    engine.Display();

    return 0;
}