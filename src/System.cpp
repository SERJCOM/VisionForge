#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <cassert>
#include <iostream>
#include <utility>

#include "VisionForge/System/System.hpp"
#include "VisionForge/Engine/Engine.hpp"





vision::System::System()
{
    using namespace std::filesystem;

    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 4.6;
    settings.minorVersion = 3;

    window_.create(sf::VideoMode({1080, 720}), "OpenGL", sf::Style::Default, settings);
    window_.setActive();
    window_.setFramerateLimit(60);

    

    main_buffer_ = vision::CreateCommonFrameBuffer(0);

    Init();

    current_path_ = std::filesystem::current_path() / path("..") / path("shaders");
    current_path_ = current_path_.lexically_normal();

    shad_ = Shader(current_path_ / path("shader.vert"), current_path_ / path("shader.frag"));
    // shadow = Shader(current_path_ / path("shadow.vert"), current_path_ / path("shadow.frag"), current_path_ / path("shadow.geom"));

    projection_ = glm::perspective(glm::radians(60.0f), (float)GetWindow().getSize().x / (float)GetWindow().getSize().y, 0.1f, 1000.0f);

    current_shader_ = &shad_;

    shad_.use();
    // shad_.setInt("point_light_shadow.depthmap", 7);

    // p_shadow.Init();

}

void vision::System::Init()
{
    glewInit();
    glEnable(GL_TEXTURE_CUBE_MAP);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glEnable(GL_MULTISAMPLE);
}

void vision::System::TurnOnCullFace()
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}


void vision::System::Drawning(int x, int y)
{
    main_buffer_->UseBuffer();
    glViewport(0, 0, x, y);
}

void vision::System::SetGameLoop(std::function<void(int &drawning)> loop)
{
    gameLoop = loop;
}

sf::Window &vision::System::GetWindow()
{
    return window_;
}

std::filesystem::path vision::System::GetCurrentPath() const
{
    return current_path_;
}

void vision::System::SetMainCamera(vision::CameraComponent *main_camera)
{
    main_camera_ = main_camera;
}

glm::mat4 vision::System::GetProjectionMatrix() const
{
    return projection_;
}

vision::CameraComponent *vision::System::GetMainCamera() const
{
    return main_camera_;
}

Shader &vision::System::GetMainShader()
{
    return shad_;
}

Shader *vision::System::GetCurrentShader()
{
    return current_shader_;
}


void vision::System::Display()
{
    int drawning = 1;

    

    ShadowManager* manager = engine_->GetEnvironmentPtr()->GetShadowManager();

    manager->Start();

    while (true)
    {
        if (drawning == 0)
        {
            break;
        }

        try
        {

            gameLoop(drawning);

            engine_->GetInputManagerPtr()->Update();

            engine_->ProcessEntities([&](IEntity* entity){
                entity->Update();
            });

            engine_->ProcessComponents([&](IComponent* comp){
                comp->Update();
            });

            engine_->GetGameClassPtr()->Update();

            manager->PrepareShadows([&](Shader& shader){
                engine_->ProcessVisualComponents([&](IVisualComponent* comp){
                    comp->Draw(shader);
                });
            });

            

            Drawning(GetWindow().getSize().x, GetWindow().getSize().y);
            main_buffer_->ClearBuffer();

            UpdateMatrix();
            UpdateShader();

            // glActiveTexture(GL_TEXTURE7);
            // glBindTexture(GL_TEXTURE_CUBE_MAP, p_shadow.GetShadowTexture());


            // shad_.setFloat("point_light_shadow.far_plane", p_shadow.far);
            // shad_.setVec3("point_light_shadow.pos", p_shadow.GetObjectPosition());

            manager->UseShadows(shad_);

            engine_->GetEnvironmentPtr()->GetLightManagerPtr()->Draw();

            

            engine_->ProcessVisualComponents([&](IVisualComponent* comp){
                comp->Draw(shad_);
            });



            Environment* env = engine_->GetEnvironmentPtr();
            env->GetSkyBoxPtr()->DrawSkyBox(view_, projection_);

            window_.display();

            // std::cout << "=======================" << std::endl;
        }
        catch (...)
        {
            std::cerr << "ERROR::UNKNOW ERROR!!!" << std::endl;
        }
    }
}


void vision::System::UpdateMatrix()
{
    view_ = main_camera_->GetViewMatrix();
}

void vision::System::UpdateShader()
{
    shad_.use();
    shad_.setMat4("projection", projection_);
    shad_.setMat4("view", view_);
    shad_.setVec3("cameraPos", main_camera_->GetObjectPosition());
}

void vision::System::SetProjectionMatrix(glm::mat4 projection)
{
    projection_ = projection;
}
