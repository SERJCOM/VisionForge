#include <iostream>
#include "window.h"
#include "engine.h"
#include "camera.h"
#include "object.h"
#include <math.h>

int main() {
	Engine::Window window(1280, 720);
	Engine::Engine engine;
	Camera camera;
	

	Object object(3);
	object.map[0].x = 0;
	object.map[0].y = 1;
	object.map[0].z = 0;

	object.map[1].x = 0.8;
	object.map[1].y = -0.5;
	object.map[1].z = 0;

	object.map[2].x = -0.8;
	object.map[2].y = -0.5;
	object.map[2].z = 0;

	camera.cameraPos = camera.SetMatrix(-1.0f, 0.0f, -2.0f);
	camera.cameraFront = camera.SetMatrix(0.0f, 0.0f, 1.0f);
	camera.cameraUp = camera.SetMatrix(0.0f, 1.0f, 0.0f);

	while (window.running) {
		camera.CameraMove();
		engine.LoadCamera(camera.cameraPos, camera.cameraFront, camera.cameraUp);
		engine.ClearBuffers();
		engine.Push(object.map, 3);
		window.Display();
	}
	return 0;
}