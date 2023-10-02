#include "VisionForge/System/System.hpp"


#include "VisionForge/Engine/Shape.hpp"
#include "VisionForge/EntitySystem/DefaulComponents/LightComponent.hpp"

#include "Entity.test.h"
#include "Model.test.h"


using namespace std;
using namespace lthm;

using filesystem::path;



int main() {

    System engine;

    filesystem::path current_path = filesystem::current_path() / path("../shaders");
    current_path = current_path.lexically_normal();
    std::cout << current_path << std::endl;


    std::shared_ptr<test::Entity> test = std::make_shared<test::Entity>(engine);
    engine.AddEntity(test);
    engine.SetMainCamera(test->GetCamera());

    path model_file = filesystem::current_path() / path("..") / path("test") / path("obj") / path("halo4") / path("scene.gltf");
    model_file.lexically_normal();
    std::shared_ptr<MEntity> model = std::make_shared<MEntity>(engine, model_file.c_str());
    engine.AddEntity(model);


    filesystem::path skybox_file = current_path / path("..") / path("test") / path("img") / path("small_empty_room_1_2k.hdr");
    skybox_file = skybox_file.lexically_normal();
    std::cout << skybox_file.c_str() << std::endl;
    Shape skybox;
    skybox.LoadRGBEfile(skybox_file.c_str());

    Shader& shad = engine.GetMainShader();
    shad.use();
    shad.SetCubeMapTexture(9, skybox.GetEnvironmentTexture(), "irradianceMap");
    shad.SetCubeMapTexture(10, skybox.GetPrefilterTexture(), "prefilterMap");
    shad.SetTexture(8, skybox.GetBDRFTexture(), "brdfLUT");




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