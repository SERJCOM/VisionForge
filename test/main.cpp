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
    engine.GetWindow().setSize(sf::Vector2u{1280, 620});

    filesystem::path current_path = filesystem::current_path() / path("../shaders");
    current_path = current_path.lexically_normal();
    std::cout << current_path << std::endl;


    std::shared_ptr<test::Entity> test = std::make_shared<test::Entity>(engine);
    engine.AddEntity(test);
    engine.SetMainCamera(test->GetCamera());


    filesystem::path skybox_file = current_path / path("..") / path("test") / path("img") / path("sky.jpg");
    skybox_file = skybox_file.lexically_normal();
    std::cout << skybox_file.c_str() << std::endl;
    Shape skybox;
    skybox.LoadRGBEfile(skybox_file.c_str());

    filesystem::path model_file = filesystem::current_path() / path("../test/obj/dimaMap/untitled.obj");
    model_file.lexically_normal();
    std::shared_ptr<MEntity> model = std::make_shared<MEntity>(engine, model_file.c_str());
    engine.AddEntity(model);

    


    bool running = true;
    
    auto loop = [&](int& drawning){

        sf::Event event;
        while(engine.GetWindow().pollEvent(event)){
            if (event.type == sf::Event::Closed)
                drawning = 0;
        }

        skybox.DrawSkyBox(engine.GetMainCamera()->GetViewMatrix(), engine.GetProjectionMatrix());

    };

    engine.SetGameLoop(loop);

    engine.Display();

    return 0;
}