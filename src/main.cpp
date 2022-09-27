#include "init.h"
#include <reactphysics3d/utils/DebugRenderer.h>
#include <SFML/Graphics/Image.hpp>



int main() {
    Window window(1080, 720);
    Engine engine;
    Camera camera(&window.window);
    Shader shad("..\\..\\shaders\\shader.vert", "..\\..\\shaders\\shader.frag");

    Shader rectangleShader("..\\..\\shaders\\rectangle.vert", "..\\..\\shaders\\rectangle.frag");

    Shadow shadow(window.GetWindowWidth(), window.GetWindowHeight());

    Model city("../../obj/de_dust2/de_dust2.obj", world, &physicsCommon); 
    city.ScaleObject(glm::vec3(0.1, 0.1, 0.1));
    city.SetObjectRotation(90, 0, 0);
    
    Mesh rect;
    rect.Create2DRectangle();

    shadow.Listening();
    

    Framebuffer fr1(1080, 720);

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
    while (window.running) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            window.window.close();
            return 0;
        }

        shadow.SetMat4();
        shadow.Listening();
        Shader shadowID = shadow.GetShader();
        city.Draw(shadowID);
        

        fr1.UseFrameBuffer();

        engine.ClearBuffers();

        camera.move();
        camera.looking(&window.window);
        camera.view = camera.updateView();
        world->update(timeStep);

        glm::mat4 projection = glm::perspective(glm::radians(80.0f), (float)window.GetWindowWidth() / (float)window.GetWindowHeight(), 0.1f, 500.0f);
        glm::mat4 view = camera.view;
        shad.use();
        shad.setMat4("projection", projection);
        shad.setMat4("view", view);
        shad.setVec3("lightPos", glm::vec3(10.0f, 50.0f, 0));


        city.Draw(shad);

        skybox.DrawSkyBox(camera.view, projection);

        engine.Drawning(window.GetWindowWidth(), window.GetWindowHeight());

        rect.DrawRectangle(rectangleShader, fr1.GetTexture());

        window.Display();
        i += 1.0f;
    }
    
    return 0;
}