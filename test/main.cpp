#include "Engine.h"

#include "Shader.h"
#include "CameraComponent.h"
#include "shape.hpp"


#include "Entity.test.h"

using namespace std;
using namespace lthm;

using filesystem::path;



int main() {

    Engine engine;
    engine.GetWindow().setSize(sf::Vector2u{1280, 620});

    filesystem::path current_path = filesystem::current_path() / path("../shaders");
    current_path = current_path.lexically_normal();
    std::cout << current_path << std::endl;


    std::shared_ptr<Entity> test = std::make_shared<Entity>(engine);
    engine.AddEntity(test);

    engine.SetMainCamera(test->GetCamera());


    filesystem::path skybox_file = current_path / path("..") / path("test") / path("img") / path("sky.jpg");
    skybox_file = skybox_file.lexically_normal();
    std::cout << skybox_file.c_str() << std::endl;

    Shape skybox;
    skybox.LoadRGBEfile(skybox_file.c_str());
    skybox.CreateHDRTexture();
    skybox.CreateEnvironment();
    skybox.CreatePrefilterMap();
    skybox.CreateBRDF();

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