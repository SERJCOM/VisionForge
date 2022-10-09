#include "init.h"
#include <reactphysics3d/utils/DebugRenderer.h>
#include <SFML/Graphics/Image.hpp>




int main() {
    Window window(1080, 720);
    Engine engine;
    Camera camera(&window.window);
    Shader shad("..\\..\\shaders\\shader.vert", "..\\..\\shaders\\shader.frag");

    Shader rectangleShader("..\\..\\shaders\\rectangle.vert", "..\\..\\shaders\\rectangle.frag");

    Shader shadow("..\\..\\shaders\\shadow.vert", "..\\..\\shaders\\shadow.frag");

    Model city1("../../obj/halo4/scene.gltf", world, &physicsCommon); 


    LightManager light;
    light.LinkShader(&shad);
    light.AddLight(0, 0.8, 0, glm::vec3(100.0f, 200.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    light.SetShaderParameters();

    Shadow shadow1(2048, 2048);
    //shadow1.SetPosition(light.GetLight(0).position);

    Shape skybox;
    std::vector<std::string> skybox_path;
    skybox_path.push_back("../../img/skymap/steini4_ft.jpg");
    skybox_path.push_back("../../img/skymap/steini4_bk.jpg");
    skybox_path.push_back("../../img/skymap/steini4_up.jpg");
    skybox_path.push_back("../../img/skymap/steini4_dn.jpg");
    skybox_path.push_back("../../img/skymap/steini4_rt.jpg");
    skybox_path.push_back("../../img/skymap/steini4_lf.jpg");
    skybox.LoadSkyBox(skybox_path);


    const decimal timeStep = 1.0f / 60.0f;
    float i = 0;
    sf::Event event;

    auto loop{
        [&](int& drawning){
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                window.window.close();
                drawning = 0;
            }
            while(window.window.pollEvent(event)){}

            camera.move();
            camera.looking(&window.window);
            camera.view = camera.updateView();
            world->update(timeStep);
            //std::cout << "cam pos: " << camera.cameraPos.x   << " " << camera.cameraPos.y << " " << camera.cameraPos.z << std::endl;
            glm::mat4 projection = glm::perspective(glm::radians(80.0f), (float)window.GetWindowWidth() / (float)window.GetWindowHeight(), 0.1f, 500.0f);
            glm::mat4 view = camera.view;


            shadow1.Listening();
            city1.Draw(shadow1.GetShader());

            engine.Drawning(window.GetWindowWidth(),window.GetWindowHeight());
            engine.ClearBuffers();

            
            shad.use();
            shad.setMat4("projection", projection);
            shad.setMat4("view", view);
            shad.setVec3("lightPos", glm::vec3(0, 50.0f, 0));
            shad.setVec3("cameraPos", camera.cameraPos);
            shad.setMat4("lightSpaceMatrix", shadow1.GetMatrix());
            shad.SetTexture(9, shadow1.GetTexture(), "shadowMap");

            city1.Draw(shad);

            skybox.DrawSkyBox(camera.view, projection);

            window.Display();

            i += 0.1f;
        }
    };

    engine.SetGameLoop(loop);

    engine.Display();
    
    return 0;
}