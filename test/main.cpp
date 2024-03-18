#include "VisionForge/Engine/Engine.hpp"

#include "VisionForge/Engine/Skybox.hpp"
#include "VisionForge/EntitySystem/DefaulComponents/LightComponent.hpp"

#include "GameClass.hpp"


#include "VisionForge/imgui/imgui_impl_glfw.h"
#include "VisionForge/imgui/imgui_impl_opengl3.h"

using namespace std;
using namespace vision;

using filesystem::path;

int main()
{
    Engine* engine = Engine::GetInstance();

    System *system = engine->GetSystemPtr();

    GameClass game;
    engine->SetGameClass(&game);

    
    bool demo_window = true;
    bool running = true;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(system->GetGLFWWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 150");

    auto loop = [&](int &drawning)    
    {
    

        int state = glfwGetKey(system->GetGLFWWindow(), GLFW_KEY_ESCAPE);
        if(state == GLFW_PRESS){
            drawning = 0;
        }
        

        // glClear(GL_COLOR_BUFFER_BIT);

        // runExample(gui);

        // gui.draw();

        
        

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if(demo_window)
            ImGui::ShowDemoWindow(&demo_window);


        ImGui::Render();
        // glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwMakeContextCurrent(system->GetGLFWWindow());


    };

    engine->GetSystemPtr()->SetGameLoop(loop);

    engine->Display();

    return 0;
}