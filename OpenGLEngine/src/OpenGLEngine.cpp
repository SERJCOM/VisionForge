#include <iostream>
#include "window.h"
#include "engine.h"
#include "camera.h"
#include "object.h"
#include <math.h>
#include "texture.h"
#include "shader.h"
#include <string>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "light.h"

int main() {



    Engine::Window window(800, 600);
    Engine::Engine engine;

    Object object1;
    Object object2;
    Object object3;

    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    object1.LoadArray(vertices, sizeof(vertices) / sizeof(float));
    object1.AddAtribute(1, 3, 6 * sizeof(float), 3 * sizeof(float));
    object1.Create();

    object2.LoadArray(vertices, sizeof(vertices) / sizeof(float));
    object2.AddAtribute(1, 3, 6 * sizeof(float), 3 * sizeof(float));
    object2.Create();

    object3.LoadArray(vertices, sizeof(vertices) / sizeof(float));
    object3.AddAtribute(1, 3, 6 * sizeof(float), 3 * sizeof(float));
    object3.Create();

    Shader shader("D:/prog/проекты VISUAL STUDIO/OpenGLEngine/OpenGLEngine/shaders/shader.vert", "D:/prog/проекты VISUAL STUDIO/OpenGLEngine/OpenGLEngine/shaders/shader.frag");

    Camera camera;

    float i = 0;

    Light light;

    while (window.running) {
        engine.ClearBuffers();
        shader.use();
        camera.move();
        camera.looking(&window.window);
        camera.view = camera.updateView();

        shader.setVec3("LIGHT.lightColor", light.lightColor);
        shader.setVec3("LIGHT.lightPos", light.lightPos);
        shader.setFloat("LIGHT.constant", 1.0f);
        shader.setFloat("LIGHT.linear", 0.09f);
        shader.setFloat("LIGHT.quadratic", 0.032f);

        shader.setVec3("cameraPos", camera.cameraPos);

        object1.SetMatrixShader(object1.modelMatrix(0.0f, 0.0f, 0.0f, 0.0f), camera.view, object1.projectionMatrix(), shader.ID);
        engine.DrawObject(object1.VAO);

        object2.SetMatrixShader(object2.modelMatrix(2.0f, 0.0f, 1.0f, 0.0f), camera.view, object2.projectionMatrix(), shader.ID);
        engine.DrawObject(object2.VAO);

        object3.SetMatrixShader(object3.modelMatrix(1.0f, 2.0f, 3.0f, 0.0f), camera.view, object3.projectionMatrix(), shader.ID);
        engine.DrawObject(object3.VAO);


        window.Display();
        i += 0.01;
    }
    return 0;
}