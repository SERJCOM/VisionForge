#include <iostream>
#include "window.h"
#include "engine.h"
#include "camera.h"



int main() {
	Engine::Window window(1280, 720);
	Engine::Engine engine;
	Camera camera;
	camera.cameraPos = camera.SetMatrix(0.0f, 1.0f, 0.0f);
	camera.cameraFront = camera.SetMatrix(0.0f, 0.0f, 0.0f);
	camera.cameraUp = camera.SetMatrix(0.0f, 1.0f, 0.0f);

	engine.LoadCamera(camera.cameraPos, camera.cameraFront, camera.cameraUp);
	while (window.running) {
		engine.ClearBuffers();
		engine.Push();
		window.Display();
	}
	return 0;
}