#include "init.h"

#include "Timer.hpp"

int main() {

    Timer time;
    time.Start();

    Window window(1920, 1080);
    Engine engine;
    Camera camera(&window.window);

    Shader shad(std::string(SHADER_PATH) + "/shader.vert", std::string(SHADER_PATH) +  "/shader.frag");
    Shader shadow(std::string(SHADER_PATH) +  "/shadow.vert", std::string(SHADER_PATH) +  "/shadow.frag");

    time.PrintTime();

    

    Li::Material matHouse;
    matHouse.AddNewMaterial("D:/prog/obj/free-quick-terrain-test/textures/diff2.jpg", Li::Type::DIFFUSE, "DefaultMaterial");
    matHouse.AddNewMaterial("D:/prog/obj/free-quick-terrain-test/textures/nrm.png", Li::Type::NORMALS, "DefaultMaterial");

    time.Start();

    Model city1("D:/prog/obj/free-quick-terrain-test/source/terrain.obj"); 

    time.PrintTime("model start");

    city1.RotateObject(90.0f, 0.0f, 0.0f);
    city1.ScaleObject(glm::vec3(0.1f, 0.1f, 0.1f));
    city1.AddMaterial(&matHouse);
    time.PrintTime("model rotate");

    city1.LoadModel();

    time.PrintTime("model Load");

    LightManager light;
    light.LinkShader(&shad);
    light.AddLight(1, 0.8, 0, glm::vec3(15.0f, 10.0f, 0.0f), glm::vec3(10000.0f, 100000.0f, 10000.0f));
    light.SetShaderParameters();

    Shape skybox;
    skybox.LoadRGBEfile("../../img/Brooklyn_Bridge_Planks/Brooklyn_Bridge_Planks_2k.hdr");
    skybox.CreateHDRTexture();
    skybox.CreateEnvironment();
    skybox.CreatePrefilterMap();
    skybox.CreateBRDF();

       
    shad.use();
    shad.SetCubeMapTexture(9, skybox.GetEnvironmentTexture(), "irradianceMap");
    shad.SetCubeMapTexture(10, skybox.GetPrefilterTexture(), "prefilterMap");
    shad.SetTexture(8, skybox.GetBDRFTexture(), "brdfLUT");

    const decimal timeStep = 1.0f / 60.0f;
    float i = 0;
    sf::Event event;

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

        //city1.SetObjectPosition(i, 0, 0);
        //city1.Draw(shad);

        skybox.DrawSkyBox(camera.view, projection);

        window.Display();

        i += 0.1f;
    };
    

    engine.SetGameLoop(loop);

    engine.Display();
    
    return 0;
}