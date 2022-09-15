#include "init.h"
#include <reactphysics3d/utils/DebugRenderer.h>
#include "physDebug.hpp"
#include <SFML/Graphics/Image.hpp>



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
    obj.CreateCollisionBox(glm::vec3(5.0f, 1.0f, 5.0f));
    obj.SetObjectPosition(20, 50.0f, 30);
    obj.UpdateObjectTransform();

    Model city("../../obj/dimaMap/untitled.obj", world, &physicsCommon);
    city.CreatePhysicsBody();
    city.CreateConcaveMeshShape();
    city.SetTypeOfThePhysObject(true);
    
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

        obj.SetObjectPosition(camera.cameraPos.x + 20, camera.cameraPos.y - 20, camera.cameraPos.z );
        obj.UpdateObjectTransform();
        obj.Draw(shad);

        city.Draw(shad);

        skybox.DrawSkyBox(camera.view, projection);

        window.Display();
        i += 0.01f;
    }
    
    return 0;
}