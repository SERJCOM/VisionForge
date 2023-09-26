#include <filesystem>

#include "Engine.h"



#include "Shader.h"
#include "CameraEntity.h"
#include "shape.hpp"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>





using namespace std;
using namespace lthm;

using filesystem::path;



int main() {

    Engine engine;
    engine.GetWindow().setSize(sf::Vector2u{1280, 620});
    CameraEntity camera(engine.GetWindow());

    filesystem::path current_path = filesystem::current_path() / path("../shaders");
    current_path = current_path.lexically_normal();
    std::cout << current_path << std::endl;

    
    Shader shad(current_path / path("shader.vert"), current_path  /  path("shader.frag"));
    Shader shadow(current_path / path("shadow.vert"), current_path / path("shadow.frag"));

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

        camera.Move();
        camera.Looking();
        camera.updateView();

        sf::Event event;
        while(engine.GetWindow().pollEvent(event)){
            if (event.type == sf::Event::Closed)
                drawning = 0;
        }
        
        //std::cout << "cam pos: " << camera.cameraPos.x   << " " << camera.cameraPos.y << " " << camera.cameraPos.z << std::endl;
        glm::mat4 projection = glm::perspective(glm::radians(80.0f), (float)engine.GetWindow().getSize().x / (float)engine.GetWindow().getSize().y, 0.1f, 1000.0f);
        glm::mat4 view = camera.view;


        engine.Drawning(engine.GetWindow().getSize().x ,engine.GetWindow().getSize().y);
        engine.ClearBuffers();

        shad.use();
        shad.setMat4("projection", projection);
        shad.setMat4("view", view);
        shad.setVec3("lightPos", glm::vec3(0, 50.0f, 0));
        shad.setVec3("cameraPos", camera.cameraPos);


        skybox.DrawSkyBox(camera.view, projection);

    };

    engine.SetGameLoop(loop);

    engine.Display();

    return 0;
}