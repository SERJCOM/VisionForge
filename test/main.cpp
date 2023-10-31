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

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                drawning = 0;
            }
    };

    engine.GetSystemPtr()->SetGameLoop(loop);

    engine.Display();

    return 0;
}