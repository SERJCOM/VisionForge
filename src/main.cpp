#include "init.h"
#include <reactphysics3d/utils/DebugRenderer.h>



int main() {
    Window window(1080, 720);
    Engine engine;
    Camera camera(&window.window);

    Shader shad("..\\..\\shaders\\shader.vert", "..\\..\\shaders\\shader.frag");
    Shader shadow("..\\..\\shaders\\shadow.vert", "..\\..\\shaders\\shadow.frag");

    Li::Material matHouse;
    matHouse.AddNewMaterial("../../../../obj/RUSSIANS HOUSES/old-house/textures/Material__25_albedo.jpg", Li::Type::DIFFUSE, "Material #25");

    Model city1("../../../../obj/RUSSIANS HOUSES/old-house/textures/1.fbx"); 
    city1.ScaleObject(glm::vec3(0.01, 0.01, 0.01));
    city1.RotateObject(90.0f, 0.0f, 0.0f);
    city1.AddMaterial(matHouse);
    city1.LoadModel();

    LightManager light;
    light.LinkShader(&shad);
    light.AddLight(0, 0.8, 0, glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    light.SetShaderParameters();

    //Shadow shadow1(2048, 2048);
    //shadow1.SetPosition(light.GetLight(0).position);

    Shape skybox;
    skybox.LoadRGBEfile("../../img/Alexs_Apartment/Alexs_Apt_2k.hdr");
    skybox.CreateHDRTexture();
    skybox.CreateEnvironment();
    skybox.CreatePrefilterMap();
    skybox.CreateBRDF();
    


    const decimal timeStep = 1.0f / 60.0f;
    float i = 0;
    sf::Event event;

    shad.use();
    shad.SetCubeMapTexture(9, skybox.GetEnvironmentTexture(), "irradianceMap");
    shad.SetCubeMapTexture(10, skybox.GetPrefilterTexture(), "prefilterMap");
    shad.SetTexture(6, skybox.GetBDRFTexture(), "brdfLUT");

    auto loop = [&](int& drawning){
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
        glm::mat4 projection = glm::perspective(glm::radians(80.0f), (float)window.GetWindowWidth() / (float)window.GetWindowHeight(), 0.1f, 1000.0f);
        glm::mat4 view = camera.view;


        engine.Drawning(window.GetWindowWidth(),window.GetWindowHeight());
        engine.ClearBuffers();

        shad.use();
        shad.setMat4("projection", projection);
        shad.setMat4("view", view);
        shad.setVec3("lightPos", glm::vec3(0, 50.0f, 0));
        shad.setVec3("cameraPos", camera.cameraPos);
        // shad.setMat4("lightSpaceMatrix", shadow1.GetMatrix());
        // shad.SetTexture(9, shadow1.GetTexture(), "shadowMap");

        city1.Draw(shad);

        skybox.DrawSkyBox(camera.view, projection);

        window.Display();

        i += 0.1f;
    };
    

    engine.SetGameLoop(loop);

    engine.Display();
    
    return 0;
}