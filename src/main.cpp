#include "init.h"
#include <reactphysics3d/utils/DebugRenderer.h>
#include "physDebug.hpp"
#include <SFML/Graphics/Image.hpp>

float skyboxVertices[] = {
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

int main() {

    world->setIsDebugRenderingEnabled(true);
    DebugRenderer& debugRenderer = world->getDebugRenderer();
    debugRenderer.setIsDebugItemDisplayed(DebugRenderer::DebugItem::COLLISION_SHAPE, true);
    debugRenderer.setIsDebugItemDisplayed(DebugRenderer::DebugItem::COLLIDER_BROADPHASE_AABB, true);
    //std::cout << debugRenderer.getNbLines() << " " << debugRenderer.getNbTriangles() <<  std::endl;

    Window window(800, 600);
    Engine engine;
    Camera camera(&window.window);
    Shader shad("..\\..\\shaders\\shader.vert", "..\\..\\shaders\\shader.frag");

                       
    Model obj("../../obj/plane/untitled.obj", world, &physicsCommon);
    obj.CreatePhysicsBody();    
    obj.CreateCollisionBox(glm::vec3(10.0f, 5.0f, 10.0f));
    obj.SetTypeOfThePhysObject(false);
    obj.SetObjectPosition(0, 100.0f, 0);
    obj.UpdateObjectTransform();
    

    Model city("../../obj/dimaMap/untitled.obj", world, &physicsCommon);
    city.CreatePhysicsBody();
    city.CreateCollisionBox(glm::vec3(30.0f, 5.0f, 30.0f));
    city.SetTypeOfThePhysObject(true);

    //Shape skybox;
    std::vector<std::string> skybox_path;
    skybox_path.push_back("../../img/skymap/steini4_ft.jpg");
    skybox_path.push_back("../../img/skymap/steini4_bk.jpg");
    skybox_path.push_back("../../img/skymap/steini4_up.jpg");
    skybox_path.push_back("../../img/skymap/steini4_dn.jpg");
    
    
    skybox_path.push_back("../../img/skymap/steini4_rt.jpg");
    skybox_path.push_back("../../img/skymap/steini4_lf.jpg");
    //skybox.LoadSkyBox(skybox_path);


    Shader skyboxShader("../../shaders/skybox.vert", "../../shaders/skybox.frag");

    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    Shape shape;
    shape.LoadSkyBox(skybox_path);

    skyboxShader.use();
    skyboxShader.setInt("skybox", 0);




    const decimal timeStep = 1.0f / 60.0f;
    float i = 0;
    while (window.running) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            window.window.close();
            return 0;
        }
        engine.ClearBuffers();
        camera.move();
        camera.looking(&window.window);
        camera.view = camera.updateView();
        //cout << camera.cameraPos.x << " " << camera.cameraPos.y << " " << camera.cameraPos.z << endl;
        world->update(timeStep);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 500.0f);
        glm::mat4 view = camera.view;
        shad.use();
        shad.setMat4("projection", projection);
        shad.setMat4("view", view);
        shad.setVec3("lightPos", glm::vec3(10.0f, 50.0f, 0));

        obj.Draw(shad);


        glDepthFunc(GL_LEQUAL); // меняем функцию глубины, чтобы обеспечить прохождение теста глубины, когда значения равны содержимому буфера глубины
        skyboxShader.use();
        view = glm::mat4(glm::mat3(camera.view)); // убираем из матрицы вида секцию, отвечающую за операцию трансляции
        skyboxShader.setMat4("view", view);
        skyboxShader.setMat4("projection", projection);
			
        // Куб скайбокса
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, shape.skyboxID);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // восстанавливаем стандартное значение функции теста глубины



        window.Display();

        //skybox.DrawSkyBox(camera.view, projection);
        i += 0.01f;
    }
    return 0;
}