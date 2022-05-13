#include "init.h"

int main() {



    Engine::Window window(800, 600);
    Engine::Engine engine;
   
    Shader sksh("D:/prog/проекты VISUAL STUDIO/OpenGLEngine/OpenGLEngine/shaders/skybox.vert", "D:/prog/проекты VISUAL STUDIO/OpenGLEngine/OpenGLEngine/shaders/skybox.frag");
    Shader shad("D:/prog/проекты VISUAL STUDIO/OpenGLEngine/OpenGLEngine/shaders/obj.vert", "D:/prog/проекты VISUAL STUDIO/OpenGLEngine/OpenGLEngine/shaders/obj.frag");
    
    Camera camera;
   
    Object sk;
    
    Model m("D:/prog/obj/Grass_Block.obj");


    float skyboxVertices[] = {
        // координаты         
       -1.0f,  1.0f, -1.0f,
       -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
       -1.0f,  1.0f, -1.0f,

       -1.0f, -1.0f,  1.0f,
       -1.0f, -1.0f, -1.0f,
       -1.0f,  1.0f, -1.0f,
       -1.0f,  1.0f, -1.0f,
       -1.0f,  1.0f,  1.0f,
       -1.0f, -1.0f,  1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

       -1.0f, -1.0f,  1.0f,
       -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
       -1.0f, -1.0f,  1.0f,

       -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
       -1.0f,  1.0f,  1.0f,
       -1.0f,  1.0f, -1.0f,

       -1.0f, -1.0f, -1.0f,
       -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
       -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
    };

    Texture skt;
    skt.LoadSkyBox();


 

    sk.LoadArray(skyboxVertices, sizeof(skyboxVertices) / sizeof(float));
    sk.stride = 3;
    sk.Create();

    
    float i = 0;
    sksh.use();
    sksh.setInt("skybox", 0);

    while (window.running) {
        engine.ClearBuffers();
        
        camera.move();
        camera.looking(&window.window);
        camera.view = camera.updateView();

       

        shad.use();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        glm::mat4 view = camera.view;
        shad.setMat4("projection", projection);
        shad.setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(5.0f, 5.0f, 5.0f)); // смещаем вниз чтобы быть в центре сцены
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// объект слишком большой для нашей сцены, поэтому немного уменьшим его
        model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        shad.setMat4("model", model);
        m.Draw(shad);

       

        // S K Y B O X 
        glDepthFunc(GL_LEQUAL);
        sksh.use();
        sk.SetMatrixShader(glm::mat4(glm::mat3(camera.updateView())), glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f), sksh.ID);
        engine.DrawSkyBox(sk.VAO, skt.skyboxID);
        glDepthFunc(GL_LESS);
        // S K Y B O X 

        window.Display();
        i += 0.01;
    }
    return 0;
}