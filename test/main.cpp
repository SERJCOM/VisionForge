#include "Engine.h"

#include "Shader.h"
#include "CameraComponent.h"
#include "shape.hpp"


#include "Entity.test.h"
#include "Model.test.h"

using namespace std;
using namespace lthm;

using filesystem::path;



int main() {

    Engine engine;
    // engine.GetWindow().setSize(sf::Vector2u{1280, 620});

    filesystem::path current_path = filesystem::current_path() / path("../shaders");
    current_path = current_path.lexically_normal();
    std::cout << current_path << std::endl;


    // std::shared_ptr<test::Entity> test = std::make_shared<test::Entity>(engine);
    // engine.AddEntity(test);
    // engine.SetMainCamera(test->GetCamera());


    CameraComponent camera(engine.GetWindow());
    engine.SetMainCamera(&camera);


    filesystem::path skybox_file = current_path / path("..") / path("test") / path("img") / path("sky.jpg");
    skybox_file = skybox_file.lexically_normal();
    std::cout << skybox_file.c_str() << std::endl;
    Shape skybox;
    skybox.LoadRGBEfile(skybox_file.c_str());

    path model_file = filesystem::current_path() / path("..") / path("test") / path("obj") / path("dimaMap") / path("untitled.obj");
    model_file.lexically_normal();
    // std::shared_ptr<MEntity> model = std::make_shared<MEntity>(engine, model_file.c_str());
    // engine.AddEntity(model);

    
    ModelComponent model(model_file.c_str());
    // model.ScaleObject(glm::vec3(10.0, 10.0, 10.0));
    model.MoveObject(0, 0, 0);
    model.LoadModel();

    bool running = true;
    
    auto loop = [&](int& drawning){

        sf::Event event;
        while(engine.GetWindow().pollEvent(event)){
            if (event.type == sf::Event::Closed)
                drawning = 0;
        }

        camera.Update();

        model.Draw(engine.GetMainShader());

        // skybox.DrawSkyBox(engine.GetMainCamera()->GetViewMatrix(), engine.GetProjectionMatrix());

    };


    engine.SetGameLoop(loop);

    engine.Display();

    return 0;
}