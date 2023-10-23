#include "VisionForge/System/System.hpp"
//#include "System.hpp"

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

    Init();

    main_buffer_ = vision::CreateCommonFrameBuffer();

    current_path_ = std::filesystem::current_path() / path("..") / path("shaders");
    current_path_ = current_path_.lexically_normal();

    shad_ = Shader(current_path_ / path("shader.vert"), current_path_ / path("shader.frag"));
    shadow_ = Shader(current_path_ / path("shadow.vert"), current_path_ / path("shadow.frag"));

    projection_ = glm::perspective(glm::radians(60.0f), (float)GetWindow().getSize().x / (float)GetWindow().getSize().y, 1.0f, 1000.0f);
}

void vision::System::Init()
{
    glewInit();
    glEnable(GL_TEXTURE_CUBE_MAP);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}

void vision::System::TurnOnCullFace()
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void vision::System::ClearBuffers()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void vision::System::Drawning(int x, int y)
{
    glViewport(0, 0, x, y);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void vision::System::SetGameLoop(std::function<void(int &drawning)> loop)
{
    gameLoop = loop;
}

sf::Window &vision::System::GetWindow()
{
    return window_;
}

void vision::System::AddEntity(std::shared_ptr<vision::IEntity> entity)
{
    entity->Start();
    entities_.push_back(entity);

    auto components = entity->GetComponents();
    for (auto component : components)
    {
        RegisterComponent(component);
    }
}
void vision::System::RegisterComponent(std::shared_ptr<vision::IComponent> component)
{
    components_.push_back(component);
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

const Shader &vision::System::GetMainShader() const
{
    return shad_;
}

void vision::System::Display()
{
    int drawning = 1;
    while (true)
    {

        if (drawning == 0)
        {
            break;
        }

        try
        {
            Drawning(GetWindow().getSize().x, GetWindow().getSize().y);
            ClearBuffers();

            UpdateMatrix();
            UpdateShader();

            gameLoop(drawning);

            for (auto entity : entities_)
            {
                entity->Update();
            }
            for (auto component : components_)
            {
                component->Update();
            }

            window_.display();
        }
        catch (...)
        {
            std::cout << "ERROR::UNKNOW ERROR!!!" << std::endl;
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
    shad_.setVec3("cameraPos", main_camera_->GetCameraPos());
}

void vision::System::SetProjectionMatrix(glm::mat4 projection)
{
    projection_ = projection;
}
