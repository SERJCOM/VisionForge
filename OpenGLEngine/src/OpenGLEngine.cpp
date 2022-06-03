#include "init.h"

int main() {
    Engine::Window window(800, 600);
    Engine::Engine engine;
    Camera camera(&window.window);
    Shader sksh("D:/prog/проекты VISUAL STUDIO/OpenGLEngine/OpenGLEngine/shaders/skybox.vert", "D:/prog/проекты VISUAL STUDIO/OpenGLEngine/OpenGLEngine/shaders/skybox.frag");
    Shader shad("D:/prog/проекты VISUAL STUDIO/OpenGLEngine/OpenGLEngine/shaders/shader.vert", "D:/prog/проекты VISUAL STUDIO/OpenGLEngine/OpenGLEngine/shaders/shader.frag");

    PhysicsCommon physicsCommon;
    PhysicsWorld* world = physicsCommon.createPhysicsWorld();

    Object sk;
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

    sksh.use();
    sksh.setInt("skybox", 0);

    Vector3 position(0, 0, 0);
    Quaternion orientation = Quaternion::identity();
    Transform transform(position, orientation);
    RigidBody* body = world->createRigidBody(transform);
    body->setType(BodyType::KINEMATIC);
    
    Vector3 halfExtents(20.0, 1.0, 20.0);
    BoxShape* boxShape = physicsCommon.createBoxShape(halfExtents);
    transform = Transform::identity();
    Collider* collider = body -> addCollider(boxShape, transform);
        


    position = Vector3(0, 20, 0);
    orientation = Quaternion::identity();
    transform.setPosition(position);
    transform.setOrientation(orientation);
    RigidBody* body1 = world->createRigidBody(transform);

    halfExtents = Vector3(1.0, 1.0, 1.0);
    BoxShape* boxShape1 = physicsCommon.createBoxShape(halfExtents);
    transform = Transform::identity();
    Collider* collider1 = body1->addCollider(boxShape1, transform);

    //Model ural("D:/prog/obj/scene.gltf");
    Model box("D:/prog/obj/colider/box.obj");
    Model box1("D:/prog/obj/colider/box.obj");
    
    const decimal timeStep = 1.0f / 60.0f;
    float i = 0;
    while (window.running) {
        engine.ClearBuffers();
        camera.move();
        camera.looking(&window.window);
        camera.view = camera.updateView();
        cout << camera.cameraPos.x << " " << camera.cameraPos.y << " " << camera.cameraPos.z << endl;
        world->update(timeStep);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        glm::mat4 view = camera.view;
        glm::mat4 model;
        shad.use();
        shad.setMat4("projection", projection);
        shad.setMat4("view", view);
        shad.setVec3("lightPos", glm::vec3(sin(i) * 8, 5.0f, cos(i) * 8));

     

        const Transform& transform = body->getTransform();
        const Vector3& position = transform.getPosition();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(position.x, position.y, position.z));
        shad.setMat4("model", model);
        box.Draw(shad);

        const Transform& transform1 = body1->getTransform();
        const Vector3& position1 = transform1.getPosition();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(position1.x, position1.y, position1.z));
        shad.setMat4("model", model);
        box1.Draw(shad);



       

        // S K Y B O X 
        {
            glDepthFunc(GL_LEQUAL);
            sksh.use();
            sk.SetMatrixShader(glm::mat4(glm::mat3(camera.updateView())), glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f), sksh.ID);
            engine.DrawSkyBox(sk.VAO, skt.skyboxID);
            glDepthFunc(GL_LESS);
        }
        // S K Y B O X 

        window.Display();
        i += 0.01;
    }
    return 0;
}