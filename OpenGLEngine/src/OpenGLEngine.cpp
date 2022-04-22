#include <iostream>
#include "window.h"
#include "engine.h"
#include "camera.h"
#include "object.h"
#include <math.h>
#include "texture.h"

int main() {
	Engine::Window window(800, 600);
	Engine::Engine engine;

	Object object1;
	Object object2;
	Object object3;
	float vertices[] = {
				0.5f,  0.5f, 0.0f,      1.0f, 1.0f,
				0.5f, -0.5f, 0.0f,      1.0f, 0.0f,
			   -0.5f, -0.5f, 0.0f,      0.0f, 0.0f,
			   -0.5f,  0.5f, 0.0f,		0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	object1.LoadArray(vertices, sizeof(vertices) / sizeof(float));
	object1.LoadArrayEBO(indices, sizeof(indices) / sizeof(int));
	object1.AddAtribute(2, 2, 5 * sizeof(float), 3 * sizeof(float));
	object1.Create();

	object2.LoadArray(vertices, sizeof(vertices) / sizeof(float));
	object2.LoadArrayEBO(indices, sizeof(indices) / sizeof(int));
	object2.AddAtribute(2, 2, 5 * sizeof(float), 3 * sizeof(float));
	object2.Create();

	Texture texture1;
	texture1.LoadTexture("skybox2.jpg");

	Texture texture2;
	texture2.LoadTexture("8_9.jpg");


	Camera camera;

	float i = 0;
	while (window.running) {
		engine.ClearBuffers();
		engine.StartDrawing();
		camera.move();
		camera.looking(&window.window);
		camera.view = camera.updateView();

		object1.SetMatrixShader(object1.modelMatrix(-3, 1, -3, i), camera.view, object1.projectionMatrix(), engine.ID);
		engine.DrawObject(object1.VAO, texture1.texture);

		object2.SetMatrixShader(object2.modelMatrix(2, -1, -1, i * 1.5), camera.view, object2.projectionMatrix(), engine.ID);
		engine.DrawObject(object2.VAO, texture2.texture);


		window.Display();
		i++;
	}
	return 0;
}