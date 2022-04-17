#include <iostream>
#include "window.h"
#include "engine.h"
#include "camera.h"
#include "object.h"
#include <math.h>

int main() {
	Engine::Window window(1280, 720);
	Engine::Engine engine;

	while (window.running) {
		engine.ClearBuffers();
		engine.Push();
		window.Display();
	}
	return 0;
}