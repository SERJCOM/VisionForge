#include "init.h"
#include <reactphysics3d/utils/DebugRenderer.h>
#include <SFML/Graphics/Image.hpp>


int main() {
    Window window(720, 720);
    Engine engine;
    Camera camera(&window.window);
    Shader shad("..\\..\\shaders\\shader.vert", "..\\..\\shaders\\shader.frag");

    Shader rectangleShader("..\\..\\shaders\\rectangle.vert", "..\\..\\shaders\\rectangle.frag");

    Shader shadow("..\\..\\shaders\\shadow.vert", "..\\..\\shaders\\shadow.frag");

    //Shadow shadow(1024, 1024);

    Model city1("../../obj/dimaMap/untitled.obj", world, &physicsCommon); 
    Model city("../../obj/testtest.obj.obj", world, &physicsCommon); 

    Shadow shadow1(1024, 1024);

    Mesh rect;
    rect.Create2DRectangle();

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


    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    unsigned int depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);
	
    // Создаем текстуры глубины
    unsigned int depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
    // Прикрепляем текстуру глубины в качестве буфера глубины для FBO
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    const decimal timeStep = 1.0f / 60.0f;
    float i = 0;

    while (window.running) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            window.window.close();
            return 0;
        }
        camera.move();
        camera.looking(&window.window);
        camera.view = camera.updateView();
        world->update(timeStep);
        std::cout << "cam pos: " << camera.cameraPos.x   << " " << camera.cameraPos.y << " " << camera.cameraPos.z << std::endl;
        glm::mat4 projection = glm::perspective(glm::radians(80.0f), 720.0f / 720.0f, 0.1f, 500.0f);
        glm::mat4 view = camera.view;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 1. Рендеринг глубины сцены в текстуру (вид - с позиции источника света)
        glm::mat4 lightView = glm::lookAt(glm::vec3(80, 30, 80), glm::vec3(0, 0, 0) , glm::vec3(0.0, 1.0, 0.0));
        //glm::mat4 lightView = camera.view;
        float near_plane = 1.0f, far_plane = 200.5f;
        glm::mat4 lightProjection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, near_plane, far_plane); 
        glm::mat4 lightSpaceMatrix = lightProjection * lightView;
		
        // Рендеринг сцены глазами источника света
        shadow.use();
        shadow.setMat4("lightSpaceMatrix", lightSpaceMatrix);

        

        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        city1.Draw(shadow);
        glActiveTexture(GL_TEXTURE0);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // Сброс настроек области просмотра
        glViewport(0, 0, 720, 720);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        shad.use();
        shad.setMat4("projection", projection);
        shad.setMat4("view", view);
        shad.setVec3("lightPos", glm::vec3(0, 50.0f, 0));
        shad.setMat4("lightSpaceMatrix", lightSpaceMatrix);

        
        glActiveTexture(GL_TEXTURE1);
        shad.setInt("shadowMap", 1);
        glBindTexture(GL_TEXTURE_2D, 5);

       
        city1.Draw(shad);

        skybox.DrawSkyBox(camera.view, projection);

        window.Display();

        i += 0.1f;
    }
    
    return 0;
}