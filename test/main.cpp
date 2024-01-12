#include "VisionForge/Engine/Engine.hpp"

#include "VisionForge/Engine/Skybox.hpp"
#include "VisionForge/EntitySystem/DefaulComponents/LightComponent.hpp"

#include "GameClass.hpp"

#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

using namespace std;
using namespace vision;

using filesystem::path;

int main()
{
    Engine engine;

    System *system = engine.GetSystemPtr();

    GameClass game;
    engine.SetGameClass(&game);

    // IMGUI_CHECKVERSION();
    // ImGui::CreateContext();
    
    // ImGuiIO& io = ImGui::GetIO(); (void)io;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; 
    // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; 

    ImGui::SFML::Init(system->GetWindow() , {1080, 720});


    sf::RenderTexture texture;
    texture.create({1080, 720});


    sf::Clock deltaClock;
    
    bool running = true;
    auto loop = [&](int &drawning)
    {
        sf::Event event;
        while (engine.GetSystemPtr()->GetWindow().pollEvent(event))
        {

            ImGui::SFML::ProcessEvent(system->GetWindow(), event);

            if (event.type == sf::Event::Closed){
                drawning = 0;
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            drawning = 0;
        }

        ImGui::SFML::Update(sf::Mouse::getPosition(), {1080, 720},  deltaClock.restart());

        ImGui::ShowDemoWindow();

        ImGui::Begin("Hello, world!");
        ImGui::Button("Look at this pretty button");
        ImGui::End();

        ImGui::EndFrame(); 

        ImGui::SFML::Render(texture);
            
    };

   

    engine.GetSystemPtr()->SetGameLoop(loop);

    engine.Display();

    ImGui::SFML::Shutdown();

    texture.getTexture().copyToImage().saveToFile("file.jpg");

    return 0;
}