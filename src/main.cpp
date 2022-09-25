#include "init.h"
#include <reactphysics3d/utils/DebugRenderer.h>
#include <SFML/Graphics/Image.hpp>



int main() {
    Window window(1080, 720);
    Engine engine;
    Camera camera(&window.window);
    Shader shad("..\\..\\shaders\\shader.vert", "..\\..\\shaders\\shader.frag");

    Shader rectangleShader("..\\..\\shaders\\rectangle.vert", "..\\..\\shaders\\rectangle.frag");

    Model obj("../../obj/plane/untitled.obj", world, &physicsCommon);
    obj.CreatePhysicsBody();    
    obj.CreateCollisionBox(glm::vec3(5.0f, 1.0f, 5.0f));
    obj.SetObjectPosition(20, 500.0f, 30);


    Model city("../../obj/de_dust2/de_dust2.obj", world, &physicsCommon); 
    // city.CreatePhysicsBody();
    // city.SetTypeOfThePhysObject(true);
    
    city.ScaleObject(glm::vec3(0.1, 0.1, 0.1));
    city.SetObjectRotation(90, 0, 0);
    // city.CreateConcaveMeshShape();
    
    Mesh rect;
    rect.Create2DRectangle(1080, 720);

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

        fr1.UseFrameBuffer();

        engine.ClearBuffers();

        camera.move();
        camera.looking(&window.window);
        camera.view = camera.updateView();
        //cout << camera.cameraPos.x << " " << camera.cameraPos.y << " " << camera.cameraPos.z << endl;
        world->update(timeStep);

        glm::mat4 projection = glm::perspective(glm::radians(80.0f), window.GetWindowWidth() / window.GetWindowHeight(), 0.1f, 500.0f);
        glm::mat4 view = camera.view;
        shad.use();
        shad.setMat4("projection", projection);
        shad.setMat4("view", view);
        shad.setVec3("lightPos", glm::vec3(10.0f, 50.0f, 0));


        //obj.Draw(shad);

        city.Draw(shad);

        skybox.DrawSkyBox(camera.view, projection);

        rect.DrawRectangle(rectangleShader, fr1.GetTexture());


        window.Display();
        i += 1.0f;
    }
    
    return 0;
}