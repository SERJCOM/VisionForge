#include "init.h"

#include "Timer.hpp"

int main() {
    Window window(1080, 720);
    Engine engine;
    Camera camera(window.window);

    Shader shad(std::string(SHADER_PATH) + "/shader.vert", std::string(SHADER_PATH) +  "/shader.frag");
    Shader shadow(std::string(SHADER_PATH) +  "/shadow.vert", std::string(SHADER_PATH) +  "/shadow.frag");
    

    Li::Material matHouse;
    matHouse.AddNewMaterial("D:/prog/obj/moon-mare-moscoviense/textures/1_Base_Color.jpg", Li::Type::DIFFUSE, "1");
    matHouse.AddNewMaterial("D:/prog/obj/moon-mare-moscoviense/textures/1_Normal_DirectX.jpg", Li::Type::NORMALS, "1");
    matHouse.AddNewMaterial("D:/prog/obj/moon-mare-moscoviense/textures/1_Mixed_AO.jpg", Li::Type::AO, "1");
    matHouse.AddNewMaterial("D:/prog/obj/moon-mare-moscoviense/textures/1_Roughness.jpg", Li::Type::ROUGHNESS, "1");
    

    Model city1("D:/prog/obj/moon-mare-moscoviense/source/Mare Moscoviense_max_LP.fbx"); 
    city1.RotateObject(90.0f, 0.0f, 0.0f);
    city1.ScaleObject(glm::vec3(0.1f, 0.1f, 0.1f));
    city1.AddMaterial(&matHouse);
    city1.MoveObject(0, -200, 0);
    city1.LoadModel();

    Li::Material mPlane;
    mPlane.AddNewMaterial("D:/prog/obj/moon-mare-moscoviense/textures/spitfire_d.png", Li::Type::DIFFUSE, "Material #85");
    mPlane.AddNewMaterial("D:/prog/obj/moon-mare-moscoviense/textures/spitfire_m.png", Li::Type::METALNESS, "Material #85");
    mPlane.AddNewMaterial("D:/prog/obj/moon-mare-moscoviense/textures/spitfire_ao.png", Li::Type::AO, "Material #85");
    mPlane.AddNewMaterial("D:/prog/obj/moon-mare-moscoviense/textures/spitfire_r.png", Li::Type::ROUGHNESS, "Material #85");

    Model plane("D:/prog/obj/supermarine-spitfire/source/spitfire.FBX");
    plane.AddMaterial(&mPlane); 
    //plane.RotateObject(0, 90, 0);
    plane.LoadModel();

    LightManager light;
    light.LinkShader(&shad);
    light.AddLight(1, 0.8, 0, glm::vec3(0.0f, 260.0f, 0.0f), glm::vec3(10000.0f, 10000.0f, 10000.0f));
    light.AddLight(1, 0.8, 0, glm::vec3(-20.0f, 260.0f, 0.0f), glm::vec3(10000.0f, 10000.0f, 10000.0f));
    light.AddLight(1, 0.8, 0, glm::vec3(50.0f, 260.0f, 1.0f), glm::vec3(10000.0f, 10000.0f, 10000.0f));
    light.SetShaderParameters();

    Shape skybox;
    skybox.LoadRGBEfile("../../img/Milkyway/Milkyway_small.hdr");
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

    auto loop = [&](int& drawning){
        if(glfwGetKey(window.window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            glfwSetWindowShouldClose(window.window, true);
            drawning = false;
        }

        camera.move();
        camera.looking(window.window);
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

        city1.Draw(shad);
        plane.Draw(shad);

        skybox.DrawSkyBox(camera.view, projection);

        window.Display();

        i += 0.1f;
    };
    

    engine.SetGameLoop(loop);

    engine.Display();
    
    return 0;
}