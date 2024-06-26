// #include <GL/glew.h>
// #include <SFML/OpenGL.hpp>
#include <cassert>
#include <iostream>
#include <utility>



#include "VisionForge/System/System.hpp"

#include "VisionForge/Engine/Engine.hpp"

#include <spdlog/spdlog.h>

#include "VisionForge/EntitySystem/DefaulComponents/ModelComponent.hpp"
// #include "System.hpp"


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    vision::Engine::GetInstance()->GetPostProcessingPtr()->SetScreenResolution(width, height);
    // projection_ = glm::perspective(glm::radians(60.0f), (float)width / height, 0.1f, 1000.0f);
}


vision::System::System()
{
    spdlog::info("System::System()");

    using namespace std::filesystem;

    // sf::ContextSettings settings;
    // settings.depthBits = 24;
    // settings.stencilBits = 8;
    // settings.antialiasingLevel = 4;
    // settings.majorVersion = 4.6;
    // settings.minorVersion = 3;

    // window_.create(sf::VideoMode({1080, 720}), "OpenGL", sf::Style::Default, settings);
    // window_.setActive();
    // window_.setFramerateLimit(60);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4.4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_ = glfwCreateWindow(1080, 720, " OpenGL", NULL, NULL);
    glfwMakeContextCurrent(window_);

    glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);

    Init();

    // InitPostProcessing();

    // blur.ConfigureBlur(1080, 720);

    // auto component = std::make_unique<ModelComponent>(std::filesystem::current_path() / path("ball.fbx"));
    // component->LoadModel();

    // visc = std::move(component);
    // visc->SetObjectPosition(glm::vec3(-112, 100, -250));
    // visc->SetObjectSize(glm::vec3(10, 10, 10));

    main_buffer_ = vision::CreateCommonFrameBuffer(-1);

    // current_path_ = std::filesystem::current_path() / path("..") / path("shaders");
    // current_path_ = current_path_.lexically_normal();

    // shad_ = Shader(current_path_ / path("shader.vert"), current_path_ / path("shader.frag"));
    shad_ = Shader(GetShaderPath("shader.vert"), GetShaderPath("shader.frag"));

    // projection_ = glm::perspective(glm::radians(60.0f), (float)GetWindow().getSize().x / (float)GetWindow().getSize().y, 0.1f, 1000.0f);

    projection_ = glm::perspective(glm::radians(60.0f), (float)1080 / 720, 0.1f, 1000.0f);


    current_shader_ = &shad_;

    shad_.use();
}

void vision::System::Init()

{
    glewInit();
    glEnable(GL_TEXTURE_CUBE_MAP);
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glEnable(GL_MULTISAMPLE);
}

void vision::System::TurnOnCullFace()
{
    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
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
    // return window_;
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

    ShadowManager *manager = Engine::GetInstance()->GetEnvironmentPtr()->GetShadowManager();

    while (true)
    {
        if (drawning == 0)
        {
            break;
        }

        try
        {

            if(glfwWindowShouldClose(window_)){
                drawning = 0;
            }

            Engine::GetInstance()->GetInputManagerPtr()->Update();

            Engine::GetInstance()->ProcessEntities([&](IEntity *entity)
                                     { entity->Update(); });

            Engine::GetInstance()->ProcessComponents([&](IComponent *comp)
                                       { comp->Update(); });

            Engine::GetInstance()->GetGameClassPtr()->Update();

            manager->PrepareShadows([&](Shader &shader)
                                    { Engine::GetInstance()->ProcessVisualComponents([&](IVisualComponent *comp)
                                                                       { comp->Draw(shader); }); });

            UpdateMatrix();
            UpdateShader();
            
            
            Drawning(GetWindowSize().first, GetWindowSize().second);
            main_buffer_->ClearBuffer();

            manager->UseShadows(shad_);

            Engine::GetInstance()->GetEnvironmentPtr()->GetLightManagerPtr()->Draw();

            // shad_.setInt("mode_render", 2);
            // visc->Draw(shad_);

            // shad_.setInt("mode_render", 1);

            Engine::GetInstance()->GetPostProcessingPtr()->Update(shad_);

            Engine::GetInstance()->ProcessVisualComponents([&](IVisualComponent *comp)
                                             { comp->Draw(shad_); });

            Environment *env = Engine::GetInstance()->GetEnvironmentPtr();
            env->GetSkyBoxPtr()->DrawSkyBox(view_, projection_);

            // UsePostProcessing(main_buffer_->GetTexture());

            Engine::GetInstance()->GetPostProcessingPtr()->UsePostProcessing(main_buffer_.get(), projection_, view_);

            gameLoop(drawning);

            // window_.display();

            glfwSwapBuffers(window_);
            glfwPollEvents();
        }
        catch (...)
        {
            std::cerr << "ERROR::UNKNOW ERROR!!!" << std::endl;
        }

    }

    glfwTerminate();
}

void vision::System::Start()
{
    ShadowManager *manager = Engine::GetInstance()->GetEnvironmentPtr()->GetShadowManager();
    manager->Start();
}
void vision::System::Render()
{
}

void vision::System::UpdateMatrix()
{
    view_ = main_camera_->GetViewMatrix();
}

void vision::System::UpdateShader()
{
    // main_buffer_->UseBuffer();
    shad_.use();
    shad_.setMat4("projection", projection_);
    shad_.setMat4("view", view_);
    shad_.setVec3("cameraPos", main_camera_->GetObjectPosition());
}

void vision::System::SetProjectionMatrix(glm::mat4 projection)
{
    projection_ = projection;
}

void vision::System::UsePostProcessing(int texture)
{
    glm::vec4 sunpos = projection_ * view_ * glm::vec4(-112, 100, -250, 1.0);

    glm::vec3 normsunpos = glm::vec3(sunpos.x / sunpos.w, sunpos.y / sunpos.w, sunpos.z / sunpos.w);

    blur.BlurTexture(main_buffer_->GetTextures()[2]);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, 1080, 720);
    glDisable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    post_processing_.use();
    glBindVertexArray(quadVAO);

    post_processing_.setInt("bloomBlur", 1);
    post_processing_.SetTexture(1, main_buffer_->GetTextures()[2], "bloomBlur");

    post_processing_.setInt("screenTexture", 15);
    post_processing_.SetTexture(15, texture, "screenTexture");

    post_processing_.setInt("godRaysSampler", 16);
    post_processing_.SetTexture(16, main_buffer_->GetTextures()[1], "godRaysSampler");

    post_processing_.setVec3("sunPos", normsunpos);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glEnable(GL_DEPTH_TEST);
}

void vision::System::InitPostProcessing()
{

    float quadVertices[] = {
        -1.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,

        -1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f};

    using namespace std::filesystem;
    current_path_ = std::filesystem::current_path() / path("..") / path("shaders");
    current_path_ = current_path_.lexically_normal();
    post_processing_ = Shader(current_path_ / path("postproc.vert"), current_path_ / path("postproc.frag"));

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
}

vision::System *vision::System::system_ptr_ = nullptr;

vision::System *vision::System::GetInstance()
{
    if(system_ptr_ == nullptr){
        system_ptr_ = new System();
    }

    return system_ptr_;
}