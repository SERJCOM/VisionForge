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
        
        if (ImGui::BeginMenu("Start game"))
        {
            ImGui::Text("This is the Cucumber tab!\nblah blah blah blah blah");
            ImGui::EndMenu();
        }
        
        if (ImGui::BeginMenu("Pause "))
        {
            ImGui::Text("This is the Cucumber tab!\nblah blah blah blah blah");
            ImGui::EndMenu();
        }
    ImGui::EndMainMenuBar();
    }
}

void ShowHierarchy(){

    bool hierarchy_bool = true;
    ImGuiWindowFlags hierarchy_flags = ImGuiWindowFlags_Modal;
    // hierarchy_flags |= ImGuiWindowFlags_
    // ImGui::SetNextWindowPos(ImVec2(5, 25));
    // ImGui::SetNextWindowSize(ImVec2(300, 300));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.0f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(65.0 / 255, 65.0 / 255, 65.0 / 255, 1));
    ImGui::Begin("Hierarchy",  &hierarchy_bool, hierarchy_flags);

    if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Hierarchy"))
            {
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

    ImGui::Text("Some text");

    ImGui::End();
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
}

void ShowProgressBar(float value){
    
    bool bar_window_bool = true;
    ImGuiWindowFlags hierarchy_flags = ImGuiWindowFlags_None;
    hierarchy_flags |= ImGuiWindowFlags_NoMove;
    hierarchy_flags |= ImGuiWindowFlags_NoCollapse;
    hierarchy_flags |= ImGuiWindowFlags_NoResize;
    hierarchy_flags |= ImGuiWindowFlags_NoTitleBar;
    hierarchy_flags |= ImGuiWindowFlags_NoScrollbar;
    
    auto win_size = vision::System::GetInstance()->GetWindowSize();
    ImGui::SetNextWindowSize(ImVec2(300, 40));
    ImGui::SetNextWindowPos(ImVec2(win_size.first - 310, win_size.second - 50));
    ImGui::Begin("progress bar", &bar_window_bool, hierarchy_flags);
    
    ImGui::ProgressBar(value / 100);

    ImGui::End();
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
            flags |= ImGuiWindowFlags_NoScrollbar;

            ImGui::Begin("Logs", &main_window, flags);

            ImGui::SetWindowPos(ImVec2(0, 0));
            ImGui::SetWindowSize(ImVec2(system->GetWindowSize().first, system->GetWindowSize().second));

            ShowMainTabs();

            ImGui::End();
        }

        ShowHierarchy();

        ShowProgressBar(70);

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