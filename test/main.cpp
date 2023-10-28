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

    // unsigned int depthCubemap;
    // glGenTextures(1, &depthCubemap);

    // const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    // glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
    // for (unsigned int i = 0; i < 6; ++i)
    //     glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, 
    //                  SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);  

    // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);  




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