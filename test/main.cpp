#include "VisionForge/Engine/Engine.hpp"

#include "VisionForge/Engine/Skybox.hpp"
#include "VisionForge/EntitySystem/DefaulComponents/LightComponent.hpp"

#include "GameClass.hpp"

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-OpenGL3.hpp>

#include "login.h"

using namespace std;
using namespace vision;

using filesystem::path;

int main()
{
    Engine engine;

    System *system = engine.GetSystemPtr();

    GameClass game;
    engine.SetGameClass(&game);

    sf::Clock deltaClock;

    tgui::Gui gui;
    gui.setWindow(system->GetWindow());

    bool running = true;
    auto loop = [&](int &drawning)    
    {
        sf::Event event;
        while (engine.GetSystemPtr()->GetWindow().pollEvent(event))
        {
            gui.handleEvent(event);
            if (event.type == sf::Event::Closed)
            {
                drawning = 0;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            drawning = 0;
        }

        // glClear(GL_COLOR_BUFFER_BIT);

        // runExample(gui);

        gui.draw();

    };

    engine.GetSystemPtr()->SetGameLoop(loop);

    engine.Display();

    return 0;
}