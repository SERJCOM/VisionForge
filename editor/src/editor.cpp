#include <VisionForge/Engine/Engine.hpp>

#include <VisionForge/Engine/Skybox.hpp>

#include "VisionForge/EntitySystem/DefaulComponents/LightComponent.hpp"
#include <VisionForge/EntitySystem/DefaulComponents/LightComponent.hpp>

#include "GameClass.hpp"

#include <VisionForge/imgui/imgui_impl_glfw.h>
#include <VisionForge/imgui/imgui_impl_opengl3.h>

using namespace std;
using namespace vision;

using filesystem::path;

void ShowMainTabs()
{

   if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Menu"))
        {
            ImGui::Text("This is the Avocado tab!\nblah blah blah blah blah");
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Window"))
        {
            ImGui::Text("This is the Broccoli tab!\nblah blah blah blah blah");
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help"))
        {
            ImGui::Text("This is the Cucumber tab!\nblah blah blah blah blah");
            ImGui::EndMenu();
        }
    ImGui::EndMainMenuBar();
    }
}

int main()
{
    Engine *engine = Engine::GetInstance();

    System *system = engine->GetSystemPtr();

    GameClass game;
    engine->SetGameClass(&game);

    bool demo_window = true;
    bool running = true;

    bool main_window = true;

    // ImGui::Windo
    //
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(system->GetGLFWWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 150");

    auto loop = [&](int &drawning)
    {
        int state = glfwGetKey(system->GetGLFWWindow(), GLFW_KEY_ESCAPE);
        if (state == GLFW_PRESS)
        {
            drawning = 0;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            ImGuiWindowFlags flags = 0;
            flags |= ImGuiWindowFlags_NoMove;
            flags |= ImGuiWindowFlags_NoResize;
            flags |= ImGuiWindowFlags_NoTitleBar;
            flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
            ImGui::Begin("Logs", &main_window, flags);

            ImGui::SetWindowPos(ImVec2(0, 0));
            ImGui::SetWindowSize(ImVec2(system->GetWindowSize().first, system->GetWindowSize().second));

            // ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

            ShowMainTabs();

            ImGui::End();
        }

        if (demo_window)
            ImGui::ShowDemoWindow(&demo_window);

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwMakeContextCurrent(system->GetGLFWWindow());
    };

    engine->GetSystemPtr()->SetGameLoop(loop);

    engine->Display();

    return 0;
}