#include "init.h"

int main() {
    Engine::Window window(800, 600);
    Engine::Engine engine;
    Camera camera(&window.window);
    Shader shad("D:/prog/проекты VISUAL STUDIO/OpenGLEngine/OpenGLEngine/shaders/shader.vert", "D:/prog/проекты VISUAL STUDIO/OpenGLEngine/OpenGLEngine/shaders/shader.frag");

                                      
    Scene scene("D:/prog/json examples/example.json");
    scene.LoadPhysics(world);
    scene.LoadScene();
    
    /*Object box("D:/prog/obj/dimaMap/untitled.obj", world);
    Object plane("D:/prog/obj/plane/untitled.obj", world);*/
    
                                                            
     
    const decimal timeStep = 1.0f / 60.0f;
    float i = 0;
    while (window.running) {
        engine.ClearBuffers();
        camera.move();
        camera.looking(&window.window);
        camera.view = camera.updateView();
        //cout << camera.cameraPos.x << " " << camera.cameraPos.y << " " << camera.cameraPos.z << endl;
        world->update(timeStep);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 500.0f);
        glm::mat4 view = camera.view;
        glm::mat4 model;
        shad.use();
        shad.setMat4("projection", projection);
        shad.setMat4("view", view);
        shad.setVec3("lightPos", glm::vec3(0.0f, 50.0f, 0.0f));
        
        //box.SetObjectPosition("mig25.WRL.cleaner.materialmerger.gles", 0, 0, -0.1);

        /*box.Draw(shad);

        plane.SetObjectPosition(0.0f, 40.0f, 0.0f);
        plane.Draw(shad);*/

        scene.DrawScene(shad);

        window.Display();
        i += 0.01;
    }
    return 0;
}