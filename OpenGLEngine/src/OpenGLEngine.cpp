#include "init.h"
#include <reactphysics3d/utils/DebugRenderer.h>
#include "physDebug.hpp"

int main() {

    world->setIsDebugRenderingEnabled(true);
    DebugRenderer& debugRenderer = world->getDebugRenderer();
    debugRenderer.setIsDebugItemDisplayed(DebugRenderer::DebugItem::COLLISION_SHAPE, true);
    debugRenderer.setIsDebugItemDisplayed(DebugRenderer::DebugItem::COLLIDER_BROADPHASE_AABB, true);
    std::cout << debugRenderer.getNbLines() << " " << debugRenderer.getNbTriangles() <<  std::endl;

    Window window(800, 600);
    Engine engine;
    Camera camera(&window.window);
    Shader shad("D:/prog/проекты VISUAL STUDIO/OpenGLEngine/OpenGLEngine/shaders/shader.vert", "D:/prog/проекты VISUAL STUDIO/OpenGLEngine/OpenGLEngine/shaders/shader.frag");

    
                       
    Model obj("D:/prog/obj/plane/untitled.obj", world, &physicsCommon);
    obj.CreatePhysicsBody();
    obj.CreateCollisionCapsule(glm::vec2(2.0f, 5.0f));
    obj.SetTypeOfThePhysObject(false);
    obj.MoveObject(0, 100, 0);

    Model city("D:/prog/obj/dimaMap/untitled.obj", world, &physicsCommon);
    city.CreatePhysicsBody();
    city.CreateCollisionBox(glm::vec3(1.0f, 5.0f, 50.0f));
    city.SetTypeOfThePhysObject(true);

    std::cout << "the size of the mesh " << sizeof(obj) << std::endl;

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


        obj.PrintObjectPosition();
        obj.UpdateObjectPosition();
        obj.Draw(shad);

        city.UpdateObjectPosition();
        city.Draw(shad);

        

        window.Display();
        i += 0.01;
    }
    return 0;
}